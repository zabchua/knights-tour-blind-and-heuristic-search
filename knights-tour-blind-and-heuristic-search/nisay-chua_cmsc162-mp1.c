#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

int n,x,y,s,M[1000000],G[1000][1000],saveX,saveY;
double time_spent = 0.0000000000000000000000000000000000000000000;

void createChessBoard(int mySelectSize, int** chessBoard){

    printf("INITIALIZE CHESS BOARD\n");
    for (int l = 0; l < mySelectSize; l++)
    {
        printf("---");
    }

    printf("\n");

    for (int i = 0; i < mySelectSize; i++)
    {

        for (int j = 0; j < mySelectSize; j++)
        {
            chessBoard[i][j] = 0;
            printf("XX ");
        }
        
        printf("\n");
        
    }
    printf("\n");

}

void printBlindSearch(int mySelectSize, int** chessBoard, FILE *bs){

    bs = fopen("blindSearch.txt", "a");

    fprintf(bs, "%s", "\n");
    fprintf(bs, "%s", "\n");
    fprintf(bs, "%s", "FINAL STATE:\n");

    for (int l = 0; l < mySelectSize; l++)
    {   
        fprintf(bs, "%s", "---");
    }

    fprintf(bs, "%s", "\n");



    for (int i = 0; i < mySelectSize; i++)
    {

        for (int j = 0; j < mySelectSize; j++)
        {
            if (chessBoard[i][j] < 10)
            {   
                fprintf(bs, "0%d ", chessBoard[i][j]);
            }
            else{
                fprintf(bs, "%d ", chessBoard[i][j]);
            }
     
        }
        fprintf(bs, "%s", "\n");
    }

    fclose(bs);

}

void initialPosition(int mySelectSize, char myStart[2], int *myVertical, int *myHorizontal, int** chessBoard, int** myLastPosition, FILE *bs){

    int v1 = 0;
    int thisV = 0;
    char v2 = 'a';
    char V2 = 'A';



    int h1 = 0;
    int H1 = 1;
    int thisH = mySelectSize - 1;

    for (int Last1 = 0; Last1 < (pow(mySelectSize, 2)); Last1++)
    {
        for (int Last2 = 0; Last2 < 2; Last2++)
        {
            myLastPosition[Last1][Last2]=0;
            
        }
        
        
    }

    

    
    while (v1 == 0)
    {
        if (myStart[0] == v2 || myStart[0] == V2)
        {
            *myVertical = thisV;
            v1 = 1;
            
            
        }
        else{
            v2 = v2 + 1;
            V2 = V2 + 1;
            thisV = thisV + 1;
            
        }
    }
    

    *myHorizontal = myStart[1]-'0';

    while (h1 == 0)
    {
        if (*myHorizontal == H1)
        {
            *myHorizontal = thisH;
            h1 = 1;
            
        }
        else{
            thisH = thisH - 1;
            H1 = H1 + 1;
        }
        
    }

    bs = fopen("blindSearch.txt", "w");

    fprintf(bs, "%s", "CMSC 162 - Machine Problem 1\n");
    fprintf(bs, "%s", "\n");
    
    fprintf(bs, "%s", "Chua, Mary Elizabeth\n");
    fprintf(bs, "%s", "Nisay, Deiondre Judd\n");
    fprintf(bs, "%s", "\n");

    fprintf(bs, "%s", "Part 1: Knight's Tour Using Blind Search\n");
    fprintf(bs, "%s", "\n");

    chessBoard[*myHorizontal][*myVertical] = 1;
    myLastPosition[0][0] = *myVertical;
    myLastPosition[0][1] = *myHorizontal;

    fprintf(bs, "%s", "INITIAL STATE:\n");

    for (int l = 0; l < mySelectSize; l++)
    {
        fprintf(bs, "%s", "---");
    }

    fprintf(bs, "%s", "\n");

    for (int i = 0; i < mySelectSize; i++)
    {

        for (int j = 0; j < mySelectSize; j++)
        {
            if (chessBoard[i][j] == 1)
            {
                fprintf(bs, "0%d ", chessBoard[i][j]);
            }
            else{
                fprintf(bs, "%s","XX ");
            }

        }
        
        fprintf(bs, "%s", "\n");
        
    }

    fclose(bs);

    
}

void checkIfZero(int mySelectSize, int** chessBoard, int *myMove){// to check if board is full

    int myStop = 0;

    for (int i = 0; i < mySelectSize; i++) 
    {
        
        for (int j = 0; j < mySelectSize; j++)
        {
            if (chessBoard[i][j]==0)
            {
                myStop = 1;
            }
            
            
        }
        
    }
    if (myStop == 0)
    {
        *myMove = 0;
    }
    
}

void blindSearch(int mySelectSize, int** chessBoard, int** myLastPosition, int *myHorizontal, int *myVertical, int *myCounter, FILE *bs){

    int myRow;
    int myCol;
    int myV;
    int myH;

    int myx;
    int myy;
    int z;

    int knightLimit = mySelectSize - 1;

    int myStop = 0;
    
    int myCheck1 = 0;
    int myCheck2 = 0;

    int myTemp = 0;

    int myEntered = 0;

    int knightMovement = 1;


    *myCounter = *myCounter + 1;
    
    

    

    while (knightMovement == 1) // up-left
    {
        
        myRow = -2;
        myCol = -1;

        myH = *myHorizontal + myRow;
        myV = *myVertical + myCol;

        if (myH < 0 || myH > knightLimit)
        {
            knightMovement = 2;
            
        }
        else if(myV < 0 || myV > knightLimit)
        {
            knightMovement = 2;
            
        }
        else if(chessBoard[myH][myV] == 1){
            knightMovement = 2;
            
        }
        else{
            myLastPosition[*myCounter][0] = myV;
            myLastPosition[*myCounter][1] = myH;
            chessBoard[myH][myV] = 1;
            


            *myHorizontal = myH;
            *myVertical = myV;
            
            
            blindSearch(mySelectSize, chessBoard, myLastPosition, &*myHorizontal, &*myVertical, &*myCounter, bs);
            
            knightMovement = 2;

            checkIfZero(mySelectSize, chessBoard, &knightMovement);

            myEntered = 1;

        }

    }

    while (knightMovement == 2) // up-right
    {
        
        myRow = -2;
        myCol = 1;

        myH = *myHorizontal + myRow;
        myV = *myVertical + myCol;



        if (myH < 0 || myH > knightLimit)
        {
            knightMovement = 3;
            
        }
        else if(myV < 0 || myV > knightLimit)
        {
            knightMovement = 3;
            
        }
        else if(chessBoard[myH][myV] == 1){
            knightMovement = 3;
            
        }
        else{
            chessBoard[myH][myV] = 1;
            myLastPosition[*myCounter][0] = myV;
            myLastPosition[*myCounter][1] = myH;


            
            *myHorizontal = myH;
            *myVertical = myV;
            
            
            blindSearch(mySelectSize, chessBoard, myLastPosition, &*myHorizontal, &*myVertical, &*myCounter, bs);
            
            knightMovement = 3;

            checkIfZero(mySelectSize, chessBoard, &knightMovement);

            myEntered = 1;

        }

    }
    while (knightMovement == 3) // up-left
    {
        
        myRow = -1;
        myCol = -2;

        myH = *myHorizontal + myRow;
        myV = *myVertical + myCol;



        if (myH < 0 || myH > knightLimit)
        {
            knightMovement = 4;
            
        }
        else if(myV < 0 || myV > knightLimit)
        {
            knightMovement = 4;
            
        }
        else if(chessBoard[myH][myV] == 1){
            knightMovement = 4;
            
        }
        else{
            chessBoard[myH][myV] = 1;
            myLastPosition[*myCounter][0] = myV;
            myLastPosition[*myCounter][1] = myH;


            
            *myHorizontal = myH;
            *myVertical = myV;
            
            
            blindSearch(mySelectSize, chessBoard, myLastPosition, &*myHorizontal, &*myVertical, &*myCounter, bs);
            
            knightMovement = 4;

            checkIfZero(mySelectSize, chessBoard, &knightMovement);


            myEntered = 1;

        }
        


    }

    while (knightMovement == 4) // up-right
    {
        
        myRow = -1;
        myCol = 2;

        myH = *myHorizontal + myRow;
        myV = *myVertical + myCol;
        


        if (myH < 0 || myH > knightLimit)
        {
            knightMovement = 5;
            
        }
        else if(myV < 0 || myV > knightLimit)
        {
            knightMovement = 5;
            
        }
        else if(chessBoard[myH][myV] == 1){
            knightMovement = 5;
            
        }
        else{
            chessBoard[myH][myV] = 1;
            myLastPosition[*myCounter][0] = myV;
            myLastPosition[*myCounter][1] = myH;
        

            
            *myHorizontal = myH;
            *myVertical = myV;
            
            
            blindSearch(mySelectSize, chessBoard, myLastPosition, &*myHorizontal, &*myVertical, &*myCounter, bs);
            
            knightMovement = 5;

            checkIfZero(mySelectSize, chessBoard, &knightMovement);

            myEntered = 1;

        }
        


    }

    while (knightMovement == 5) // down-right
    {
        
        myRow = 1;
        myCol = 2;

        myH = *myHorizontal + myRow;
        myV = *myVertical + myCol;
        


        if (myH < 0 || myH > knightLimit)
        {
            knightMovement = 6;
            
        }
        else if(myV < 0 || myV > knightLimit)
        {
            knightMovement = 6;
            
        }
        else if(chessBoard[myH][myV] == 1){
            knightMovement = 6;
            
        }
        else{
            myLastPosition[*myCounter][0] = myV;
            myLastPosition[*myCounter][1] = myH;
            
            chessBoard[myH][myV] = 1;
            
            
            *myHorizontal = myH;
            *myVertical = myV;
            
            
            blindSearch(mySelectSize, chessBoard, myLastPosition, &*myHorizontal, &*myVertical, &*myCounter, bs);
            
            knightMovement = 6;

            checkIfZero(mySelectSize, chessBoard, &knightMovement);

            myEntered = 1;

        }
        


    }

    while (knightMovement == 6) // down-left
    {
        
        myRow = 1;
        myCol = -2;

        myH = *myHorizontal + myRow;
        myV = *myVertical + myCol;


        if (myH < 0 || myH > knightLimit)
        {
            knightMovement = 7;
            
        }
        else if(myV < 0 || myV > knightLimit)
        {
            knightMovement = 7;
            
        }
        else if(chessBoard[myH][myV] == 1){
            knightMovement = 7;
            
        }
        else{
            myLastPosition[*myCounter][0] = myV;
             myLastPosition[*myCounter][1] = myH;
            chessBoard[myH][myV] = 1;
            

            
            *myHorizontal = myH;
            *myVertical = myV;
            
            
            blindSearch(mySelectSize, chessBoard, myLastPosition, &*myHorizontal, &*myVertical, &*myCounter, bs);
            
            knightMovement = 7;

            checkIfZero(mySelectSize, chessBoard, &knightMovement);


            myEntered = 1;

        }
        


    }
    while (knightMovement == 7) // up-left
    {
        
        myRow = 2;
        myCol = -1;

        myH = *myHorizontal + myRow;
        myV = *myVertical + myCol;


        if (myH < 0 || myH > knightLimit)
        {
            knightMovement = 8;
            
        }
        else if(myV < 0 || myV > knightLimit)
        {
            knightMovement = 8;
            
        }
        else if(chessBoard[myH][myV] == 1){
            knightMovement = 8;
            
        }
        else{
            myLastPosition[*myCounter][0] = myV;
            myLastPosition[*myCounter][1] = myH;
            chessBoard[myH][myV] = 1;


            
            *myHorizontal = myH;
            *myVertical = myV;
            
            
            blindSearch(mySelectSize, chessBoard, myLastPosition, &*myHorizontal, &*myVertical, &*myCounter, bs);
            
            knightMovement = 8;

            checkIfZero(mySelectSize, chessBoard, &knightMovement);


            myEntered = 1;

        }
        


    }

    while (knightMovement == 8) // up-right
    {
        
        myRow = 2;
        myCol = 1;

        myH = *myHorizontal + myRow;
        myV = *myVertical + myCol;
        
       
            
        

        if (myH < 0 || myH > knightLimit)
        {
            knightMovement = 9;
            

        }
        else if(myV < 0 || myV > knightLimit)
        {
            knightMovement = 9;
            
        }
        else if(chessBoard[myH][myV] == 1){
            knightMovement = 9;
            
            
            checkIfZero(mySelectSize, chessBoard, &knightMovement);
        }
        else{
            myLastPosition[*myCounter][0] = myV;
            myLastPosition[*myCounter][1] = myH;
            chessBoard[myH][myV] = 1;
            

           
            
            *myHorizontal = myH;
            *myVertical = myV;
            
            
            blindSearch(mySelectSize, chessBoard, myLastPosition, &*myHorizontal, &*myVertical, &*myCounter, bs);
            
            knightMovement = 9;
            
            checkIfZero(mySelectSize, chessBoard, &knightMovement);

            

            myEntered = 1;
            

        }
        


    }

    

    if (knightMovement == 9 && *myCounter>1)
    {
        
        if(myEntered == 1){
        chessBoard[myLastPosition[*myCounter][1]][myLastPosition[*myCounter][0]] = 0;
        }
            


        myTemp = *myCounter - 2;
        *myCounter = *myCounter - 1;

        chessBoard[myLastPosition[*myCounter][1]][myLastPosition[*myCounter][0]] = 0;
                
        
        *myHorizontal = myLastPosition[myTemp][1];
        *myVertical = myLastPosition[myTemp][0];

        
    }
    else if(knightMovement == 0 && *myCounter > 1){
       
        *myCounter = *myCounter - 1;
     
    }
    else if(knightMovement == 9 && *myCounter == 1){
        printf("Knight's Tour unsolvable with this starting position!\n");
    }
    
    else if (knightMovement == 0 && *myCounter == 1)
    {

        z=1;

        for (int Last1 = 0; Last1 < (pow(mySelectSize,2)); Last1++)
        {   
            
            for (int Last2 = 0; Last2 < 2; Last2++)
            {
                if (Last2 == 0)
                {
                    myy = myLastPosition[Last1][Last2];
                }
                else{
                    myx = myLastPosition[Last1][Last2];
                    chessBoard[myx][myy]= z;
                    z=z+1;
                }
                         
            }

        }
        
        printBlindSearch(mySelectSize, chessBoard, bs);
        printf("\n");
    
    }
    

}

void jump(int d)
{
	if(M[s]==0)
	{
		x = x - 1*d;
		y = y + 2*d;
	}
	else if(M[s]==1)
	{
		x = x - 2*d;
		y = y + 1*d;
	}
	else if(M[s]==2)
	{
		x = x - 2*d;
		y = y - 1*d;
	}
	else if(M[s]==3)
	{
		x = x - 1*d;
		y = y - 2*d;
	}
	else if(M[s]==4)
	{
		x = x + 1*d;
		y = y - 2*d;
	}
	else if(M[s]==5)
	{
		x = x + 2*d;
		y = y - 1*d;
	}
	else if(M[s]==6)
	{
		x = x + 2*d;
		y = y + 1*d;
	}
	else if(M[s]==7)
	{
		x = x + 1*d;
		y = y + 2*d;
	}
}

int count()
{
	int count=0;
	if((x-1)>=0 && (y+2)<n && G[x-1][y+2]==-1)
		count++;
	if((x-2)>=0 && (y+1)<n && G[x-2][y+1]==-1)
		count++;
	if((x-2)>=0 && (y-1)>=0 && G[x-2][y-1]==-1)
		count++;
	if((x-1)>=0 && (y-2)>=0 && G[x-1][y-2]==-1)
		count++;
	if((x+1)<n && (y-2)>=0 && G[x+1][y-2]==-1)
		count++;
	if((x+2)<n && (y-1)>=0 && G[x+2][y-1]==-1)
		count++;
	if((x+2)<n && (y+1)<n && G[x+2][y+1]==-1)
		count++;
	if((x+1)<n && (y+2)<n && G[x+1][y+2]==-1)
		count++;
	return count;	
}

//Warnsdorff
int heuristicSearch(){
	int x1,y1,c,d,min=n,dist,min_dist,gd,gm;
	clock_t begin = clock();


	for(s=0;;s++){
		G[x][y]=s;
		min=8;
		d=0;
		for(M[s]=0;M[s]<8;M[s]++){
			jump(1);
			if(x>=0&&x<n && y>=0&&y<n && G[x][y]==-1){
				c=count();
				dist=(x-n/2)*(x-n/2)+(y-n/2)*(y-n/2);
				if(c<min || (c==min&&dist>min_dist)){
					min=count();
					d=M[s];
					min_dist=dist;
				}
			}
			jump(-1);	
		}
		if(min==8)
			break;
		
		M[s]=d;
		jump(1);
	}
	clock_t end = clock();
	time_spent += (double)(end - begin) / CLOCKS_PER_SEC;

	// Print to text file

	
	FILE *out=fopen("heuristicMethodSolutions.txt","w");

	fputs("CMSC 162 - Machine Problem 1\n\n",out);
	fputs("Chua, Mary Elizabeth\n",out);
	fputs("Nisay, Deiondre Judd\n\n",out);

	fputs("Part 2: Knight's Tour Using Heuristic Search (Warnsdorf's Rule)\n",out);
	fputs("SOURCE CODE: Bhatt, J (2020) Knight_s_Tour.c [Source code]. https://github.com/Jwalin1/C-programs/blob/master/Algorithms/Knight_s_Tour.c\n\n",out);

	fputs("INITIAL STATE: (Can start from either zero or one)\n",out);
	fputs("------------------\n",out);
	for (int i=0; i<n; i++)
	{
		for (int j=0; j<n; j++)
		{
			if(i==saveX&&j==saveY)
			fprintf(out, "01 ");
			else
			fprintf(out, "XX ");
		}
		fprintf(out, "\n");
	}
	fprintf(out, "\n\n");

	fputs("FINAL STATE: (Partial solution. The final solution must show all the steps from 0/1 - 63/64)\n",out);
	fputs("------------------\n",out);
	for (x=0; x<n; x++)
	{
		for (y=0; y<n; y++)
		{
			fprintf(out, "%02d ", G[x][y] + 1);
		}
		fprintf(out, "\n");
	}
	fprintf(out, "\nRUNTIME:   %.100lf seconds", time_spent);
	
	fclose(out);

	if(s+1==n*n)
		printf("\nsolution found\n");
	else
		printf("\nstuck\n");

	getchar();
	return 0;
}


int main(){

    int myEntire = 0;

    while (myEntire == 0)
    {

    double blindSearchTime = 0.0;

    int myHour, myMinute;
    float mySecond;

    int mySelectSize;
    int mySelectTemp = 0;
    char myStart[2];
    int myVertical;
    int myHorizontal;
    int m = 64;
    int myn = 2;

    int myConsider0 = 0;
    int myConsider1 = 0;
    int myConsider2 = 0;
    int myConsider3 = 0;

    char limit, position[2];
	int first, second;
    

    int mySearchChoice;

    


    FILE *bs;

    
        while (myConsider0 == 0)
        {
            printf("\n\nChoose a search method:\n");
            printf("1 - Blind Search\n");
            printf("2 - Heuristic Search\n\n");
            printf("Input number of choice:");
            scanf("%d", &mySearchChoice);

            if (mySearchChoice == 1 || mySearchChoice == 2)
            {
                myConsider0 = 1;
            }
            else{
                printf("Not a valid input. Please try again. \n \n");
            }
            

        }
    

    
        if (mySearchChoice == 1)
        {
            while (myConsider1 == 0)
            {
                printf("Enter size of board (limit is 9): ");
                scanf("%d", &mySelectSize);
                if (mySelectSize < 10 && mySelectSize > 0)
                {
                    myConsider1 = 1;
                }
                else{
                    printf("Chess board size should be more than 0 and less than 10!\n");
                }
                
            }
            myConsider1 == 0;
            

            


            mySelectTemp = mySelectSize;

            int **myLastPosition=(int **)malloc(m * sizeof(int *));
            for (int i = 0; i < m; i++)
            {
                myLastPosition[i] = (int *)malloc(myn * sizeof(int));
            }

            int myCounter = 0;

            

            

            printf("\n");

            int **chessBoard=(int **)malloc(mySelectSize * sizeof(int *));
            for (int i = 0; i < mySelectSize; i++)
            {
                chessBoard[i] = (int *)malloc(mySelectSize * sizeof(int));
            }
            
            createChessBoard(mySelectTemp, chessBoard);

            while (myConsider2 == 0)
            {
                printf("Input Starting Position: ");
                scanf("%s", &myStart);
                if (myStart[0] < ('a' + mySelectTemp) && myStart[0] >= 'a' && (myStart[1] - '0') <= mySelectTemp)
                {
                    myConsider2 = 1;
                }
                
            }

            myConsider2 = 0;
            
            
            

            clock_t myBegin = clock();

            initialPosition(mySelectTemp, myStart, &myVertical, &myHorizontal, chessBoard, myLastPosition, bs);

            

            blindSearch(mySelectTemp, chessBoard, myLastPosition, &myHorizontal, &myVertical, &myCounter, bs);



            clock_t myEnd = clock();

            blindSearchTime += (double)(myEnd - myBegin) / CLOCKS_PER_SEC;

            myHour = blindSearchTime / 3600;
            myMinute = (blindSearchTime - (myHour*3600))/60;
            mySecond = blindSearchTime - (myHour*3600)- (myMinute*60);


            bs = fopen("blindSearch.txt", "a");

            fprintf(bs, "%s", "\n");
            fprintf(bs, "%s", "\n");

            if (myHour < 1)
            {
                if (myMinute < 1)
                {
                    fprintf(bs, "RUNTIME: %f seconds\n \n", blindSearchTime);
                }
                else if (myMinute == 1)
                {
                    fprintf(bs, "RUNTIME: %d minute: %f seconds\n \n", myMinute, mySecond);
                }
                
                else{
                    fprintf(bs, "RUNTIME: %d minutes: %f seconds\n \n", myMinute, mySecond);
                }
                
            }
            else if (myHour == 1)
            {
                fprintf(bs, "RUNTIME: %d hour, %d minutes: %f seconds\n \n", myHour, myMinute,mySecond);
            }
            
            else{
                fprintf(bs, "RUNTIME: %d hours, %d minutes: %f seconds\n \n", myHour, myMinute,mySecond);
            }
            


            fclose(bs);

            

            printf("Knight's Tour has been generated, open blindSearch.txt for the results!\n\n");

            while (myConsider3 == 0)
            {
                printf("Choose your next action:\n");
                printf("0 - Restart\n");
                printf("1 - Terminate\n");
                printf("Input number of choice:");
                scanf("%d", &myEntire);

                if (myEntire == 0 || myEntire == 1)
                {
                    myConsider3 = 1;
                }
                else{
                    printf("Not a valid input. Please try again. \n \n");
                }
                

            }


            }
            else if (mySearchChoice == 2)
            {

                

                while (myConsider1 == 0)
                {
                    printf("Enter size of board (limit is 9): ");
                    scanf("%d", &n);
                    getchar();
                    if (n < 10 && n > 0)
                    {
                        myConsider1 = 1;
                    }
                    else{
                        printf("Chess board size should be more than 0 and less than 10!\n");
                    }
                    
                }

                myConsider1 = 0;

                for(x=0;x<n;x++)
                    for(y=0;y<n;y++)
                        G[x][y] = -1;
                
                limit = (n+48)+'0';

                printf("Enter starting position (a1-%c%d): ", limit, n);

                scanf("%c%c", &position[0], &position[1]);

                first = position[0] - '0' -48;
                second = position[1] - '0';



                x = n - second;
                y = first-1;
                saveX = x;
                saveY = y;


                heuristicSearch();

                printf("Knight's Tour has been generated, open heuristicMethodSolution.txt for the results!\n\n");

                while (myConsider3 == 0)
                {
                    printf("Choose your next action:\n");
                    printf("0 - Restart\n");
                    printf("1 - Terminate\n");
                    printf("Input number of choice:");
                    scanf("%d", &myEntire);

                    if (myEntire == 0 || myEntire == 1)
                    {
                        myConsider3 = 1;
                    }
                    else{
                        printf("Not a valid input. Please try again. \n \n");
                    }
                    

                }




            }
        }

    
    printf("\n \n ====Thank you====\n\n");


    return 0;
}

