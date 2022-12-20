# mitkadem_ex2
Advanced programming assighnment 2.
How to run: 
1. dowload the files.
2. in the terminal print : make
3. then print: ./a.out k source_file distance.
4. write down a vector you want to classifi.

How it works:
The program get from the command line three parameters: 
1. the program also get number k to count k nearest neighbors and type of distance to calculate the distance and check if it an integer and if not it exit and print error.
2. csv file root or name if the file is in current directory. if the file does not exist the program will exit and pront an error.
if there is a good csv file it turns the classification strings to numbers, and turn the file to vector of double vectors where each vector contain the flower parameters and numeric classification.
The program checks if all the parammeters are numeric, and the vectors are the right size if not will exit program and print error.
3. distamce. it check it such a distance can be calculated using this program and if not it exits and print an error.
after all this tests the program create object of the class KNN and define the input parameters as class parameters.

Then the user give the program vector of numbers. if the vector is not the right size, or not all numeric the program will throw error.
The program will calculate the distance between the vector recives and every vector in the class parameter. If the distance function tries to divide by zero the program skip the vector. The calculated distance and the classification is added to vector of distances sized k. The vector is sorted and if it is bigger thean k the biggest distance is deleted. 
After calculating all the distances the program is left with k smallest distances and their classification. The program count each classification and returns 
the one that repeat the most.
If there are 2 possible classification that apears in equal numbers in the smallest distances vector, the program will choose the one that represented by the lowar number.
the classification is been printed to the screen and the program is waiting for another vercor to be printed by user.
