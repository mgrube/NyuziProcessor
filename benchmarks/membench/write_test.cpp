// 
// Copyright (C) 2011-2014 Jeff Bush
// 
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Library General Public
// License as published by the Free Software Foundation; either
// version 2 of the License, or (at your option) any later version.
// 
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Library General Public License for more details.
// 
// You should have received a copy of the GNU Library General Public
// License along with this library; if not, write to the
// Free Software Foundation, Inc., 51 Franklin St, Fifth Floor,
// Boston, MA  02110-1301, USA.
// 


#define NUM_STRANDS 4
#define LOOP_UNROLL 8

typedef int veci16 __attribute__((__vector_size__(16 * sizeof(int))));

const int kTransferSize = 0x100000;
void * const region1Base = (void*) 0x200000;

int main()
{
	veci16 *dest = (veci16*) region1Base + __builtin_nyuzi_read_control_reg(0) * LOOP_UNROLL;
	veci16 values = __builtin_nyuzi_makevectori(0xdeadbeef);
	
	int transferCount = kTransferSize / (64 * NUM_STRANDS * LOOP_UNROLL);
	do
	{
		dest[0] = values;
		dest[1] = values;
		dest[2] = values;
		dest[3] = values;
		dest[4] = values;
		dest[5] = values;
		dest[6] = values;
		dest[7] = values;
		dest += NUM_STRANDS * LOOP_UNROLL;
	}
	while (--transferCount);
}
