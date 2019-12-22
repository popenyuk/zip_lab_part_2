# zip_lab_part_2
## Introduction
This program extracts the specified archive into memory, after which it opens each .txt file and counts the total number of words in all files and outputs the results to the specified file.
## Implementing our thread-safe queue
In the main thread, the program creates the required number of threads for reading files and counting the number of words. Also, it creates the required number of threads to combine the number of words.
Then in the main thread, it unzips each .txt file and adds it to the queue of strings.
In reading threads, the text is divided into words, then the number of words in that text is counted and written to the corresponding dictionary.
In merging threads, it gets two dictionaries, and then join it into one dictionary.
All this happens until the archive is completely processed, and only one dictionary is left.
It is implemented with queues, maps, threads, mutexes, and condition variables. 
Unfortunately, it is implemented as a class of God, that is, all in one class.

## Installation and compilation
  ```bash
  $ git clone https://github.com/popenyuk/zip_lab_part_2
  $ cd zip_lab_part_2
  $ mkdir build
  $ cd build
  $ cmake -G"Unix Makefiles" ..
  $ cd ..
  $ cd bin
  $ make
  ```
  
## Running
  <i>(Inside the <b>bin</b> directory)</i><br>
  <b>CPP FILE</b><br>
  <b>One thread file:</b><br>
    ```
    $ ./_5_one_thread <configuration_file>
    ```<br>
  <b>Multi thread file:</b><br>
    ```
    $ ./_5_multi_thread <configuration_file>
    ```<br>
	
## Running script
   	From any directory of project, except directory of project, run
	python3 ../script/word_script.py number both ../config.txt, where number is number of repetitions
	
## Results
	It is tested on an 8 Gb archive of TXT files.
	Multi thread and one thread shows the same results
	Winning 13 %
  


## License and copyright
© Yevhenii Molodtsov, Zenovii Popeniuk and Serhii Rosovskyi, students of the Ukrainian Catholic University


