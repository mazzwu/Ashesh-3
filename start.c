  PageRank(d, diffPR, maxIterations)

  // d = damping factor
  // The damping factor is the probability at each step
  // that the person will just stop searching through links lol

  //diffPR: Difference in page rank sum 

  // MaxIterations - 


            Read "web pages" from the collection in file "collection.txt"
            and build a graph structure

            //FILE *col = fopen("collection.txt", "r")

            N = number of urls in the collection
              //Initialise int N = 0; 

          // To find the number of urls in the collection 

           // Write a function that counts the number of strings in a collection?
            //char urlincol[10000];
            //while(fscanf(col, "%s", urlincol) != EOF){
            // N++ }
        }
    

            

            // Begin For Loop 
            // For loop sets the page rank for each URL in collection to
            //1/Number of URLS in the collection 

            For each url pi in the collection
                PR(pi) = 1/N  ;

                // They are referring to each url as pi
                // It could have also said: For each url, x, in the collection
                // PR(x) =1/N;
                // Instead they have said PR(pi)=1/N;

                // This means The page rank of pi is = 1/N. 


	    End For 


            iteration = 0;
            diff = diffPR;   // to enter the following loop

            // Question about this step - If you are setting 
            // diff = diffPR - when will it not be = to each other?
            // Nevermind - diff is reset in while loop

            While (iteration < maxIteration AND diff >= diffPR)
                iteration++;
	        diff = 0;    // reset diff for each iteration

                For each url pi in the collection

                    PR_old = PR(pi);
                    // What is PR_old? // Where does this value come from?
                    sum = 0 ;

                    For each url pj pointing to pi (ignore self-loops and parallel edges)
                    // lol we just learnt about parallel edges in discrete - 
                    // If you dont remember what this means just ask me. 
                              sum = sum + PR(pj) / out-degree-of(pj);

                              // I think in this function we should read through the URL.txt files until we 
                              // find a URL.TXT file that has pi in it. 


	            End For


                    PR(pi) = (1-d)/N + d * sum // Just calculations 
	            diff = diff + Abs(PR_old - PR(pi); // Still dont understand what PR_old is 

	        End For 

	     End While
    