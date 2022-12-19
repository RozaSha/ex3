# mitkadem_ex2
Advanced programming assighnment 2.
How to run:
How it works:
The program get from the user csv file, turn the classification strings to numbers, and turn the file to vector of double 
vectors where each vector contain the flower parameters and numeric classification. The program checks if all the parammeters are numeric, 
if the classification fits to the expected classification, and the vectors are the right size.
the program also get number k to count k nearest neighbors and type of distance to calculate the distance.
The program create object of the class KNN and define the input parameters as class parameters. 
The user give the program vector of numbers. if the vector is not the right size, or not all numeric the program will throw error.
The program will calculate the distance between the vector recives and every vector in the class parameter. If the distance function tries to divide
by zero the program skip the vector. The calculated distance and the classification is added to vector of distances sized k. The vector is sorted and 
if it is bigger thean k the biggest distance is deleted. 
After calculating all the distances the program is left with k smallest distances and their classification. The program count each classification and returns 
the one that repeat the most.
