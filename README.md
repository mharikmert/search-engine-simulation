## Ranking-Documents-for-Information-Retrieval-with-Priority-Queues

### How it works
User searchs for a word and the program try to find the word in documents under the files folder. <br>
Number of the existance of the word for every file is found and these numbers are set to the max binomial heap, in this way, numbers are sorted in heap. <br> 
File names and file contents are also hold in binomial heap. <br> 
Lastly a defined number of documents on the top of the heap is printed to the user. <br>
It is a small-scale search engine for words.  

## How to use
You can add the texts and files that to be searched for to files folder. <br>
You can also changed the number of documents that contains the word are displayed after the searching. <br> 

![Screenshot from 2021-03-15 20-40-19](https://user-images.githubusercontent.com/42295478/111196927-e82db980-85ce-11eb-81be-adee0896a502.png)

![Screenshot from 2021-03-15 20-40-35](https://user-images.githubusercontent.com/42295478/111196910-e4019c00-85ce-11eb-813f-7597351ea388.png)






### Clone, Compile and Run  
```
  -> git clone https://github.com/mharikmert/Ranking-Documents-for-Information-Retrieval-with-Priority-Queues
  -> gcc -o main main.c
  -> ./main

```
