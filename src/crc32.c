#include <stdio.h>
#include <stdlib.h>

#define BUFSIZE 1024*4


/* Calculate crc32 of a given Value */
uint32_t crc32_arm64_le_hw( uint32_t crc, const uint8_t *p, unsigned int len )
{
	int64_t length = len;

	while ( ( length -= sizeof( uint64_t ) ) >= 0 ) {
		CRC32X( crc, *( ( uint64_t * ) p ) );
		p += sizeof( uint64_t );
	}

	if ( length & sizeof( uint32_t ) ) {
		CRC32W( crc, *( ( uint32_t * ) p ) );
		p += sizeof( uint32_t );
	}
	if ( length & sizeof( uint16_t ) ) {
		CRC32H( crc, * ( ( uint16_t * ) p ) );
		p += sizeof( uint16_t );
	}
	if ( length & sizeof( uint8_t ) )
		CRC32B( crc, *p );

	return crc;
}

/* Calculate crc32c of a given Value */
uint32_t crc32c_arm64_le_hw( uint32_t crc, const uint8_t *p, unsigned int len )
{
	int64_t length = len;

	while ( ( length -= sizeof( uint64_t ) ) >= 0 ) {
		CRC32CX( crc, *( ( uint64_t * ) p ) );
		p += sizeof( uint64_t );
	}

	if ( length & sizeof( uint32_t ) ) {
		CRC32CW( crc, *( ( uint32_t * ) p ) );
		p += sizeof( uint32_t );
	}
	if ( length & sizeof( uint16_t ) ) {
		CRC32CH(crc, *( ( uint16_t * ) p ) );
		p += sizeof( uint16_t );
	}
	if ( length & sizeof( uint8_t ) )
		CRC32CB( crc, *p );

	return crc;
}

int main( int argc, char **argv ){
	uint8_t buf[ BUFSIZE ];
	if( argc < 2 ){
		return -1;
	}
	for ( int i = 1; i < argc; i++ ){
		FILE *fp	= fopen( argv[ i ], "rb" );
		if( fp == NULL ){
			printf( "%s: No such file or directory\n", argv[ 0 ] );
			return 1; 
		}
		uint32_t nread	=0;
		uint32_t crc	=~0;
		for(;;){
			nread	= fread( buf, sizeof( uint8_t ), BUFSIZE, fp );
			if( nread > 0 ){
				crc = crc32_arm64_le_hw( crc, buf, nread );
			}else
				break;
		}
		if( argc > 2 ){
			printf( "%x	%s\n", ~crc, argv[ i ] );
		}else{
			printf( "%x\n", ~crc );
		}
		fclose( fp );
	}
	return 0;
}
