# zip_lab_part_2

## Counting the number of words in a text file. Part two, our thread-safe queue and dispatching
## Introduction
This program counts the number of each words in input files using its own queue and dispatching.

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


