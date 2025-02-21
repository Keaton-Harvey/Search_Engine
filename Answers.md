# Assignment 4: Answers

**Complete this document, commit your changes to Github and submit the repository URL to Canvas.** Keep your answers short and precise.

Names of all team members:
Keaton Harvey
Daymien Zavala
Sam Skanse

Used free extension: [x] 24 hrs or [ ] 48 hrs

[ ] Early submission (48 hrs)

[ ] Bonus work. Describe: ...

Place [x] for what applies.


## Answers

### Project Management

Complete the tasks and planned completion columns **BEFORE** You start with 
coding!


Weekly milestones/tasks. Set out a plan at the beginning and then record when you got it done.

https://docs.google.com/spreadsheets/d/1WV0txrGKobABsvPgWDmc_yREvMIKIRw897tfWLm6nm4/edit?usp=sharing

| Task        | Planned completion | Actual completion | Time spent in hrs by X | Time spent in hrs by Y |
| ----------- | :-----------------:| :---------------: | :--------------------: | :--------------------: |
| x           | Nov 3              | Nov 6             | 8.5                    | 0                      |


### High-level Design of Solution

- Add a UML class diagram, etc. 
- High-level pseudo code for each component.

### Used Data Structures
Explanation of what data structures are used where. For each, state
    - time and space complexity (Big-Oh),

    - why it is the appropriate data structure and what other data structure could have been used.

    In our search engine, we use maps, vectors, arrays, and trees. These data structures were appropriate for the following reasons: 

    maps O(n)- we needed maps because we needed to collect elements in key-value pairs. (words and relevancy, combinations)

    vectors O(N) - we needed vectors because it allowed for efficient insertion and deletion of elements. (words from document, stop word functions, file paths, words, persons, orgs, not words)

    tree - allow for quick and easy access to data (parsed and lowercased words)

### User Documentation
- What are the features of your software?

The features of our software consist of our Index Handler, AVL Tree Map, Document Parser, Search Engine, Query Processor, and UI. All of these work together utilizing complicated vectors, 2D vectors, maps, unordered sets, tree, etc.   

- Describe how to use the software. 

To use the software, the user must choose 1 of the 6 options we provide. They can either create an index from a directory with documents, write the index to a file, read an index from a file, enter a query, output statistics of the search engine, or exit the search engine. 

- Some example queries with the results.

query -> tax
-------------------------------------

Title: Press Releases - CNBC
URL: http://www.cnbc.com/2018/02/28/pr-newswire-eaton-vance-closed-end-funds-release-estimated-sources-of-distributions.html
----------------------------------------

Title: Archive News &amp; Video for Tuesday, 27 Feb 2018 | Reuters.com
URL: https://www.reuters.com/article/brief-francescas-sees-q4-2017-gaap-earni/brief-francescas-sees-q4-2017-gaap-earnings-per-share-0-07-to-0-11-idUSASB0C7UA

--------------------------------------

query -> quarter PERSON:francesca
-------------------------------------

Title: Archive News &amp; Video for Tuesday, 27 Feb 2018 | Reuters.com
URL: https://www.reuters.com/article/brief-francescas-sees-q4-2017-gaap-earni/brief-francescas-sees-q4-2017-gaap-earnings-per-share-0-07-to-0-11-idUSASB0C7UA
----------------------------------------

### Performance
- Provide statistics (word counts, timing, etc) for indexing all documents (or as many as you can in a reasonable amount of time).

Timing of Indexing from Directory: 0.0300176 
Timing of Indexing from File: 140548
Timing of Processing Query: 140548
Total unique words indexed: 327
Total unique articles for current index: 6

### Bonus Work
Did you attempt any bonuses? If so, please give a brief description of what you did.

   > n/a