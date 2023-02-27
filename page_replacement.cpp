#include<bits/stdc++.h>
#include<fstream> // to perform file operations 

using namespace std;
// page replace algorithm is used to manage the memory of buffer and to decide which pages to keep
// and which pages must be discarded to reduce faults and increase success rate


void fifo(int pages[], int total_pages, int frame_size){

/* FIFO - first in first out algorithm

	as the name of the algorithm says which page or data file comes first it allocates the memory 
	to it and if the buffer is full it discards the very first page inserted in the buffer and 
	allocates that space to the page and thus continues

Algorithm : 

- take input of total number of pages, frame size of buffer and actual pages to be stored in buffer
as total_pages, frame_size, and pages respectively ;

- In the fifo function create an array of size (frame_size), with all values initially as -1;
since every frame of that buffer is empty initially

- initialize -> ;a boolean to check if the page is already there in the buffer,
;an integer to keep the track of the column in which we are going to allocate the new page,
;an integer to keep the track of number of faults

- print total_pages, frame_size, all pages 

- loop over all the pages stored in the pages array to perform operation over every page

- for each page loop over the buffer array to check if the page exists  in the buffer

- if the page exists , flag = false and break out of loop(since page already exists)

- if page doesn't exists, flag = true and  increment fault by 1, insert the page in buffer at 
precise column 

-  after the above check check if column number is greater than frame_size then reset it to 0

- print all pages currently stored in buffer

- print fualt rate 
- end

 */

	int buffer[frame_size]; // initializing the buffer of given frame size 
	memset(buffer, -1, frame_size*sizeof(int)); // setting all elements of the buffer to -1 initially
	bool flag = true; // flag to check if element is present in the buffer 
	int column = 0; // coloumn to keep the track of current coloumn
	int fault = 0; // count of faults

	// printing the gathered data
	cout << "\nFIFO Algorithm : ";
	cout << "\nFrame size : " << frame_size;
	cout << "\nTotal number of pages : " << total_pages;
	cout << "\nPages : ";
	for(int i=0;i<total_pages;i++) cout << pages[i] << " ";
	cout << "\n";

	for(int i=0;i<total_pages;i++){ // looping over the pages
		for(int j=0;j<frame_size;j++){ // looping over the buffer to check if page already exists
			flag = true; // if page not found setting flag to true every time until found
			if(pages[i] == buffer[j]){ // if found set to false and break out of loop
				flag = false;
				break;
			}
		}
		if(flag == true){ // flag is true means there is a fault 
			fault++; // so increment fault
			if(column >= frame_size) column = 0; // check if number of columns is greater than 
													// frame size if so reset columns to 0
			buffer[column] = pages[i]; // allocate that position to current page
			column++;
		}
		for(int j=0;j<frame_size;j++){ // printing the pages of buffer
			cout << buffer[j] << " ";
		}
		cout << "\n";
	}	

	cout << "Faults : " << fault << "\n"; // number of faults

}


void lru(int pages[], int total_pages, int frame_size){

/* LRU - Least Recently Used algorithm
	as the name of the algorithm says any page or data file in the buffer which has not been used 
	very recently that is the page which must be replaced by the new page. 

Algorithm : 

- take input of total number of pages, frame size of buffer and actual pages to be stored in buffer
as total_pages, frame_size, and pages respectively ;

- In the lru function create an array of size (frame_size), with all values initially as -1;
since every frame of that buffer is empty initially

- initialize -> ;a boolean to check if the page is already there in the buffer,
;an integer to keep the track of the column in which we are going to allocate the new page,
;an integer to keep the track of number of faults
;an array with all values as -1 intially to keep a counter of least recently used elements
;an extra flag to check if the intial frame is passed

- print total_pages, frame_size, all pages 

- loop over all the pages stored in the pages array to perform operation over every page

- for each page loop over the buffer array to check if the page exists  in the buffer

- if page exists then flag = false,  update the value of counter with position same as the position
of the page existing in buffer and break;

- if the page doesn't exists flag = true;

- if flage is true then increment the fault by 1, 
;check if column number is greater than frame size if true then,
;set col = 0 and intial frames flag = true;(as the intial set of frames is passed)
;find the minimum value in the counter array and set min as that value
;also the column value will be the index of that value in counter as we need to replace the page on 
that index in buffer, which has minimum value (meaning it is least recently used)
;update counter's value at that index as the current page's index as well as replace the page at
that index with current page. increment the column value; 

- print all pages currently stored in buffer

- print fault rate 
- end


 */

	int buffer[frame_size], counter[frame_size]; // initializing the buffer to store pages
	memset(buffer, -1, frame_size*sizeof(int)); // setting all elements of buffer to -1 since empty at start
	memset(counter, -1, frame_size*sizeof(int)); // setting all elements of counter to -1 
	bool flag = false; // flag to check fault
	int column = 0; // to keep track of columns
	int fault = 0; // to keep track of faults
	bool frame_passed = false; // flag to check if the first frame is passed

	// printing the gathered data
	cout << "\nLRU Algorithm : ";
	cout << "\nFrame size : " << frame_size;
	cout << "\nTotal number of pages : " << total_pages;
	cout << "\nPages : ";
	for(int i=0;i<total_pages;i++) cout << pages[i] << " ";
	cout << "\n";

	for(int i=0;i<total_pages;i++){ // looping over all pages
		for(int j=0;j<frame_size;j++){ // looping over the buffer to check if page exists
			flag = true; // if not found setting flag to true until found
			if(pages[i] == buffer[j]){ // if found , flag = false and break out of loop
				flag = false;
				counter[j] = i;
				break;
			}
		}
		if(flag == true){ // if page not found 
				fault++; // increment fault
				if(column>=frame_size){ // if column count is greater than frame size
					column = 0;			// reset it to zero
					frame_passed = true;// and set frame passed as true since the first frame is filled with pages
				}
				int min = counter[0]; // to store the least recently used page
				for(int j=0;j<frame_size;j++){ // loop over buffer to find the minimum element
					if(counter[j] < min && counter[j] != -1){// and non negative
						min = counter[j]; // if found min = that minimum element
						column = j; // and column = the index at which that element is present
					}
				}
				if(min == counter[0] && frame_passed == true){ // if the min is the first element in counter
					column = 0; // and first frame is passed only then set column to 0 otherwise nope
				}
				counter[column] = i; // set value at column^th index in counter to i (i.e. current page's index)
				buffer[column] = pages[i];// replace the page at that index with current page
				column++; // increment column count
		}

		for(int j=0;j<frame_size;j++) cout << buffer[j] << " "; // printing the pages in buffer
		cout << "\n";

	}

	cout << "Faults : " << fault << "\n";

}


void optimal(int pages[], int total_pages, int frame_size)
{
/* Optimal page replacement algorithm

	This is the most optimal algorithm in the algorithms of page replacement
	since it decides the replacement of a page in the buffer on the future basis
	it checks which page in the buffer is the farthest from the current index of pages
	and replaces the page which is the farthest

Algorithm : 

- take input of total number of pages, frame size of buffer and actual pages to be stored in buffer
as total_pages, frame_size, and pages respectively ;

- In the optimal function create an array of size (frame_size), with all values initially as -1;
since every frame of that buffer is empty initially

- initialize -> ;a boolean to check if the page is already there in the buffer,
;an integer to keep the track of the column in which we are going to allocate the new page,
;an integer to keep the track of number of faults
;a boolean to check if the intial frame is passed

- print total_pages, frame_size, all pages 

- loop over all the pages stored in the pages array to perform operation over every page

- for each page loop over the buffer array to check if the page exists or not in the buffer

- if the page exists , set flag = false and break;

- if page doesn't exists, flag = true;

- if flag is true, then
; increment fault by 1
; check if the intial frame is passed
; if the intial frame is passed then
; search for the farthest page in pages which is also present in the buffer
; and store its index to replace it
; if intial frame not passed then simply insert into buffer

- print all pages currently stored in buffer

- print fualt rate 
- end

 */

	int buffer[frame_size]; // intializing the buffer to store pages
	memset(buffer, -1, frame_size*sizeof(int)); // setting all elements of buffer to -1 since empty at start
	bool flag = true; // flag to check if page exists
	int column = 0; // to keep the track of current column
	int fault = 0; // to keep the track of faults
	bool frame_passed = false; // to check if the initial frame is passed

	for(int i=0;i<total_pages;i++){ // looping over the pages
		for(int j=0;j<frame_size;j++){ // looping in the buffer to check if the current page exists in it
			flag = true; // setting flag to true until page not found
			if(buffer[j] == pages[i]){ // if found set flag to false and break out of loop
				flag = false;
				break;
			}
		}
		if(flag == true){ // if flag is true that means there is fault
			fault ++; // increment fault
			if(column >= frame_size){ // if the column count is greater than frame size reset it to 0
				column = 0;
				frame_passed = true; // and set the frame passed flag to true
			}
			

			if(frame_passed == true){ // if the intial frame is passed then check in the buffer which page is 
										// farthest in the list of pages
				// index to be replaced , location where it occurs for first
				int to_replace = -1, farthest = i + 1;

				for(int j=0;j<frame_size;j++){ // looping over the buffer 
					int k;
					for(k=i+1;k<total_pages;k++){ // looping over the pages to check where does farthest page occur
						if(buffer[j] == pages[k]){ // if the page is found which also in buffer 
							if(k > farthest){ // and it's index is greater than the index of current frame's last element
								farthest = k; // set it to farthest
								to_replace = j; // also store the index to replace page at that index
							}
							break;
						}
					}
					if(k == total_pages){ // if it is the last page store it to replace
						to_replace = j;
						break;
					}
				}
			
				if(to_replace == -1){ // if no such page found then replace the first page in the buffer
					column = 0; // thus column = 0
				}
				else{
						column = to_replace; // if found set it as column to replace
				}

			}

			buffer[column] = pages[i]; // replace the page at column^th index to current page
			column++; // increment the column count
		}
		for(int j=0;j<frame_size;j++) cout << buffer[j] << " "; // printing all pages
		cout << "\n";
	}

	cout << "Faults : " << fault << "\n";

}


int main(){

	int choice; // to store the choice

	// MENU
		cout << "-------------------MENU----------------";
		cout << "\n1. FIFO\n";
		cout << "2. LRU\n";
		cout << "3. Optimal\n";
		cout << "0. Exit\n";	
		cin >> choice;

		if(choice == 0){
			cout << "Program terminated...\n";
			return 0;
		}

		int total_pages, frame_size;
		cout << "\nEnter the total number of pages : ";
		cin >> total_pages;
		cout << "\nEnter the frame size of the buffer : ";
		cin >> frame_size;

		int pages[total_pages];
		cout << "\nEnter the pages : ";
		for(int i=0;i<total_pages;i++) cin >> pages[i];
		cout << "\n";
		switch(choice){
			case 1:
				fifo(pages , total_pages, frame_size);
				break;
			case 2:
				lru(pages, total_pages, frame_size);
				break;
			case 3:
				optimal(pages, total_pages, frame_size);
				break;
			default: 
				cout << "\nEnter the valid choice !!!\n";
		}

	return 0;
}

