#include<stdio.h>
#include<math.h>
int main(){
    int n,m,flag;
    while(scanf("%d %d",&m,&n)!=EOF){
        flag = 0;
        for(int i=m;i<=n;i++){
            if(pow(i/100,3)+pow(i/10%10,3)+pow(i%10,3) == i){
                if(flag !=0 ) printf(" ");
                printf("%d",i);
                flag = 1;
            }
        }
    if(flag==0) printf("no");
    printf("\n");
    }
}
