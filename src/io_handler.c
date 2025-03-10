#include "io_handler.h"
#include "lower_dev.h"
#include "NvmBlkPoolManager/blk_pool.h"

int nvm_cache_handle_io(NvmCache *cache, NvmCacheIoReq *req) {

    int ret;
    uint64_t lba_offset = 0;


    //判断具体请求是读还是写
    if(req->dir == CACHE_READ)
    {
        while(lba_offset < req->lba_num)
        {
            uint64_t *nvmBlkPtr = NULL;
            nvmBlkPtr = searchNvmBlkOfLba(cache->blk_pool, req->lba + lba_offset);
    
            //判断lba是否在nvmBlk中，若在，进入内部逻辑，不在，直接转发至lower_dev接口
            if(nvmBlkPtr)
            {
                //TODO
                //通过nvmBlkId读取对应的Nvm块，存放至对应的buffer对应的偏移中
            }
            else
            {                
                LowerDevIoReq *lower_req;
                lower_req = kmalloc(sizeof(LowerDevIoReq), GFP_KERNEL);
                if (!lower_req) {
                    pr_err("Error: Failed to allocate memory for LowerDevIoReq\n");
                    return -ENOMEM;
                }

                lower_req->sector     = req->lba + lba_offset;      // 不确定是否可以使用上层传来的 lba 作为起始扇区号
                lower_req->sector_num = 1;                          // 目前一次只发送一个sector
                lower_req->buffer     = req->buffer + lba_offset * CACHE_BLOCK_SIZE;
                lower_req->dir        = req->dir;

                ret = lower_dev_io(cache->lower_bdev, lower_req);
                if (ret != 0) 
                {
                    pr_err("Error: IO request failed for LBA: %llu, sector: %llu, sector_num: %llu\n", 
                           req->lba, lower_req->sector, lower_req->sector_num);
                }

                kfree(lower_req);  // 释放内存，避免泄露
            }
            lba_offset++;
        }


    }
    else
    {
        while(lba_offset < req->lba_num)
        {
            uint64_t *nvmBlkPtr = NULL;
            nvmBlkPtr = searchNvmBlkOfLba(cache->blk_pool, req->lba + lba_offset);
    
            //判断lba是否在nvmBlk中，若在，进入内部逻辑，不在，直接转发至lower_dev接口
            if(nvmBlkPtr)
            {
                //TODO
                //通过nvmBlkId写对应的Nvm块，存放至对应的buffer对应的偏移中
            }
            else
            {
                ret = getEmptyBlock(cache->blk_pool, nvmBlkPtr);
                if(ret == 1 && *nvmBlkPtr == UINT64_MAX)
                {
                    pr_err("Error: blk_pool allocation failed. Invalid block ID (nvmBlkPtr: %llu) for lba: %llu\n", 
                        *nvmBlkPtr, req->lba + lba_offset);
                }

                //如果返回的nvm块有效且已被分配，需要先将其写回，得到空闲的块后在进行写操作
                if(ret)
                {   
                    void *write_back_buffer = NULL;
                    write_back_buffer = kmalloc(CACHE_BLOCK_SIZE, GFP_KERNEL);
                    if (!write_back_buffer) 
                    {
                        pr_err("Failed to allocate memory for write_back_buffer\n");  
                        return -ENOMEM;    
                    }

                    uint64_t *write_back_lba = NULL;

                    //
                    //TODO:查询nvm上的映射数组，将*nvmBlkPtr转化为对应的lba号，写入*write_back_lba。
                    
                    if(write_back_lba == NULL)
                    {
                        pr_err("Error: Failed to find NVM block for LBA, nvmBlkPtr=%llu\n", *nvmBlkPtr);
                    }

                    //
                    //TODO:将数据从nvm块中读到write_back_buffer中，为下一步写回做准备
                    //

                    LowerDevIoReq *lower_req;
                    lower_req = kmalloc(sizeof(LowerDevIoReq), GFP_KERNEL);
                    if (!lower_req) {
                        pr_err("Error: Failed to allocate memory for LowerDevIoReq\n");
                        return -ENOMEM;
                    }

                    lower_req->sector     = *write_back_lba;     // 不确定是否可以使用上层传来的 lba 作为起始扇区号
                    lower_req->sector_num = 1;             // 目前一次只发送一个sector
                    lower_req->buffer     = write_back_buffer;
                    lower_req->dir        = req->dir;
    
                    ret = lower_dev_io(cache->lower_bdev, lower_req);
                    if (ret != 0) 
                    {
                        pr_err("Error: IO request failed for LBA: %llu, sector: %llu, sector_num: %llu\n", 
                               req->lba, lower_req->sector, lower_req->sector_num);
                    }
                    
                    //
                    //TODO: 对nvmBlkId进行写操作
                    //

                    //在blk_pool中进行记录
                    buildNvmBlock(cache->blk_pool, nvmBlkPtr, req->lba + lba_offset);

                    kfree(lower_req);      // 释放 lower_req 内存
                    kfree(write_back_buffer);  // 释放 write_back_buffer 内存
                }
            }
            lba_offset++;
        }
    }
    return 0;
}