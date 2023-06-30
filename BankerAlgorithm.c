#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
void safesequence(int **,int **,int *,int **,int,int);
void resreq(int **,int **,int *,int *,int **,int,int,int);
int main()
{
        int choice;
                int res_no,pr_no,**max,**all,*avail,**need;
                int *req,p_no;
                int i,j;
                printf("ENTER THE NUMBER OF RESOURCES :");
                scanf("%d",&res_no);
                printf("ENTER THE NUMBER OF PROCESS :");
                scanf("%d",&pr_no);
                /* DYNAMIC MEMORY ALLOCATION */
                req = (int *)malloc(res_no * sizeof(int));
                avail = (int *)malloc(res_no * sizeof(int));
                max = (int **)malloc(pr_no * sizeof(int*));
                all = (int **)malloc(pr_no * sizeof(int*));
                need = (int **)malloc(pr_no * sizeof(int*));
                for(i=0;i<pr_no;i++)
                {
                        max[i] = (int*)malloc(res_no * sizeof(int));
                        all[i] = (int*)malloc(res_no * sizeof(int));
                        need[i] = (int*)malloc(res_no * sizeof(int));
                }
                printf("\n");
                for(i=0;i<pr_no;i++)
                {
                        printf("ENTER THE MAX INSTANCES OF EACH RESOURCES FOR P""%d" ":" ,i+1);
                        for(j=0;j<res_no;j++)
                        {
                                scanf("%d",&max[i][j]);
                        }
                }
                printf("\n");
                for(i=0;i<pr_no;i++)
                {
                        printf("ENTER THE RESOURCE ALLOCATION FOR P""%d" ":",i+1);
                        for(j=0;j<res_no;j++)
                        {
                                scanf("%d",&all[i][j]);
                        }
                }
                printf("\n");
                printf("ENTER THE AVAILABLE RESOURCES :");
                for(i=0;i<res_no;i++)
                {
                        scanf("%d",&avail[i]);
                }
                do{
                        for(i=0;i<pr_no;i++)
                        {
                                for(j=0;j<res_no;j++)
                                {
                                        need[i][j] = max[i][j] - all[i][j];
                                }
                        }
                        printf("\n");
                        printf("ENTER 1 TO KNOW THE STATE OF SYSTEM\n");
                        printf("ENTER 2 FOR REQUESTING RESOURSE\n");
                        printf("ENTER THE CHOICE :");
                        printf("\n");
                        scanf("%d",&choice);
                        if(choice==1)
                        {
                                safesequence(all,max,avail,need,res_no,pr_no);
                        }
                        else if(choice==2)
                        {
                                printf("ENTER THE RESOURCES TO BE REQUESTED TO THE PROCESS :");
                                for(i=0;i<res_no;i++)
                                {
                                        scanf("%d",&req[i]);
                                }
                                printf("ENTER THE PROCESS FOR WHICH THE RESOURCES IS TO BE ALLOCATED :");
                                scanf("%d",&p_no);
                                resreq(all,max,req,avail,need,res_no,pr_no,p_no);
                        }
                        else
                        {
                                printf("!!PLEASE ENTER THE VALIC OPTION!!");
                        }
        }while(choice!=0);

}

void safesequence(int **all,int **max,int *avail,int **need,int res_no,int pr_no)
{
        /* safe sequence function to detect whether the system is in safe state or not */
        int i,j,count,out1[pr_no],flag=0;
        int k ,out[res_no],s = 0,l,a = 0;
        bool tel = true;
        int out3[res_no],out5[pr_no];
        printf("\n--------------------------\n");
        printf("MAXIMUM");
        for(i=0;i<pr_no;i++)
        {
                printf("\n");
                for(j=0;j<res_no;j++)
                {
                        printf("%d ",max[i][j]);
                }
        }
        printf("\n--------------------------\n");
        printf("\nALLOCATION");
        for(i=0;i<pr_no;i++)
        {
                printf("\n");
                for(j=0;j<res_no;j++)
                {
                        printf("%d ",all[i][j]);
                }
        }
        printf("\n--------------------------\n");
        printf("NEED ");
        for(i=0;i<pr_no;i++)
        {
                printf("\n");
                for(j=0;j<res_no;j++)
                {
                        printf("%d ",need[i][j]);
                }
        }
        for(i=0;i<res_no;i++)
        {
                out5[i] = 0;
        }
        for(i=0;i<res_no;i++)
        {
                out3[i] = 0;
        }
        for(i=0;i<pr_no;i++)
        {
                for(j=0;j<res_no;j++)
                {
                        out3[j] = out3[j] + all[i][j];
                }
                printf("%d",out3[i]);
        }
        for(i=0;i<res_no;i++)
        {
                out3[i] = out3[i] + avail[i];
        }
        printf("\nTOTAL MATRIX :");
        for(i=0;i<res_no;i++)
        {
                printf("%d\t",out3[i]);
        }
        for(i=0;i<res_no;i++)
        {
                out1[i] = -1;
        }
        for(i=0;i<res_no;i++)
        {
                out[i] = avail[i];
        }
        for(i=0;i<pr_no;i++)
        {
                count = 0;
                for(j=0;j<res_no;j++)
                {
                        if(out5[j] == i+1)
                                continue;
                }
                for(j=0;j<res_no;j++)
                {
                        if(need[i][j]<= out[j])
                        {
                                count = count + 1;
                        }
                }
                if(count == res_no)
                {
                        for(k=0;k<res_no;k++)
                        {
                                out[k] = out[k] + all[i][k];
                        }
                        for(l=0;l<res_no;l++)
                        {
                                need[i][l] = 999;
                        }
                        out1[s] = i+1;
                        s++;
                        out5[a] = i+1;
                        a++;
                }
                if(s==pr_no)
                {
                        break;
                }
                else if(i==pr_no-1 && s==0)
                {
                        break;
                }
                else if(i==pr_no-1 && s!=pr_no)
                {
                        i = 0;
                }
        }
        printf("\nAFTER PROCESSING ALGORIHTM\n");
        for(i=0;i<res_no;i++)
        {
                printf("%d\t",out[i]);
        }
        printf("\n\n");
        printf("SAFE SEQUENCE\n");
        printf("<");
        for(i=0;i<pr_no;i++)
        {
                if(out1[i]!=-1){
                        printf("P%d\t",out1[i]);
                }
                else{
                        flag=1;
                }
        }
        printf(">");
        printf("\n\n");
        int ld = sizeof(out5)/sizeof(int);
        if(flag!=1)
        {
                printf("THE SYSTEM IS IN SAFE STATE");
        }
        else{
                printf("THE SYSTEM IS NOT IN SAFE STATE");
        }
        printf("\n");
}

void resreq(int **all,int **max,int *req,int *avail,int **need,int res_no,int pr_no,int p_no)
{
        int out4[res_no],out5[res_no],out6[res_no];
        int i,j,a=0,flag = 0;
        for(i=0;i<res_no;i++)
        {
                all[p_no-1][i] = all[p_no-1][i] + req[i];
                avail[i] = avail[i] - req[i];
                need[p_no-1][i] = need[p_no-1][i] - req[i];
        }
        int count,out1[pr_no];
        int k ,out[res_no],s = 0,l;
        bool tel = true;
        int out2[res_no];
        printf("NEED ");
        for(i=0;i<pr_no;i++)
        {
                printf("\n");
                for(j=0;j<res_no;j++)
                {
                        printf("%d ",need[i][j]);
                }
        }
        for(i=0;i<res_no;i++)
        {
                out2[i] = 0;
        }
        for(i=0;i<pr_no;i++)
        {
                for(j=0;j<res_no;j++)
                {
                        out2[j] = out2[j] + all[i][j];
                }
        }
        for(i=0;i<res_no;i++)
        {
                out2[i] = out2[i] + avail[i];
        }
        for(i=0;i<res_no;i++)
        {
                out1[i] = -1;
        }
        for(i=0;i<res_no;i++)
        {
                out[i] = avail[i];
        }
        for(i=0;i<pr_no;i++)
        {
                count = 0;
                for(j=0;j<res_no;j++)
                {
                        if(out5[j] == i+1)
                                continue;
                }
                for(j=0;j<res_no;j++)
                {
                        if(need[i][j]<= out[j])
                        {
                                count = count + 1;
                        }
                }
                if(count == res_no)
                {
                        for(k=0;k<res_no;k++)
                        {
                                out[k] = out[k] + all[i][k];
                        }
                        out1[s] = i+1;
                        s++;
                        for(l=0;l<res_no;l++)
                        {
                                need[i][l] = 999;
                        }
                        out5[a] = i+1;
                        a++;
                }
                if(s==pr_no)
                {
                        break;
                }
                else if(i==pr_no-1 && s==0)
                {
                        break;
                }
                else if(i==pr_no-1 && s!=pr_no)
                {
                        i = 0;
                }
        }
        printf("\n");
        for(i=0;i<res_no;i++)
        {
                if(req[i]>max[p_no-1][i])
                {
                        printf("THE REQUEST CANNOT BE GRANTED SINCE THE REQUEST RESOURCE IS GREATER THAN THE MAX RESOURCE");
                        flag = 1;
                        break;
                }
        }
        printf("\n");
        if(flag!=1)
        {
                printf("AFTER PROCESSING ALGORIHTM\n");
                for(i=0;i<res_no;i++)
                {
                        printf("%d\t",out[i]);
                }
        }
        printf("\n\n");
        printf("TOTAL MATRIX\n");
        for(i=0;i<res_no;i++)
        {
                printf("%d\t",out2[i]);
        }
        printf("\n\n");
        printf("SAFE SEQUENCE\n");
        printf("<");
        for(i=0;i<pr_no;i++)
        {
                if(flag!=1)
                {
                        printf("P%d\t",out1[i]);
                }
        }
        printf(">");
        printf("\n\n");
        if(flag!=1)
        {
                printf("THE SYSTEM IS IN SAFE STATE\n");
                printf("THE REQUEST CAN BE GRANTED\n");
        }
        else{
                printf("THE SYSTEM IS NOT IN SAFE STATE\n");
                printf("THE REQUEST CANNOT BE GRANTED\n");
        }

}
