#ifndef FS_LOW
#define FS_LOW

//
// Start Partition System
//
// This is the first function to call before your filesystem starts
// If the filename already exists, then the input values stored in
// volSize and blockSize are ignored.  If the file does not exist, it will
// be created to the specified volume size in units of the block size
// (must be power of 2) plus one for the partition header.
//
// On return
// 		return value 0 = success;
//		return value -1 = file exists but can not open for write
//		return value -2 = insufficient space for the volume
//		volSize will be filled with the volume size
//		blockSize will be filled with the block size
#include <stdint.h>
typedef unsigned long long ull_t;

int startPartitionSystem (char * filename, uint64_t * volSize, uint64_t * blockSize);

int closePartitionSystem ();

uint64_t LBAwrite (void * buffer, uint64_t lbaCount, uint64_t lbaPosition);

uint64_t LBAread (void * buffer, uint64_t lbaCount, uint64_t lbaPosition);

#define MINBLOCKSIZE 512
#define PART_SIGNATURE	0x526F626572742042
#define PART_SIGNATURE2	0x4220747265626F52
#define PART_CAPTION "CSC-415 - Operating Systems File System Project Header\n\n"

#define	PART_ACTIVE 		1
#define	PART_INACTIVE 		0

#define	PART_NOERROR 		0
#define PART_ERR_INVALID	-4

typedef struct partitionInfo {
	char 		volumePrefix[sizeof(PART_CAPTION)+2];
	uint64_t	signature;
	uint64_t	volumesize;
	uint64_t	blocksize;
	uint64_t	numberOfBlocks;
	char * 		filename;			//Never written - always assigned on start
	int			fd;					//Never Written - file descriptor
	uint64_t	signature2;
	char		volumeName[];
	} partitionInfo_t, * partitionInfo_p;

extern partitionInfo_p partInfop;

#endif // FS_LOW



