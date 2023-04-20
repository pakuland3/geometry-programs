#include <stdio.h>
#include <string.h>
#include <math.h>
#include <unistd.h>

/*K1 = 50       z' = 사람과 화면사이 거리 K1 고정상수 
  K2 = 5        K2는 사람과 도넛사이 최대거리 
  R1 = 1
  R2 = 2
*/

int k;
//double sin() ,cos(); //의미 없는 부분 
main(){
    const size_t width = 80; //80
	const size_t height = 22; //22
	const size_t buffer_size = height * width; //화면 가로 크기 : 80 세로 22
	int R1=1, //원래 1 
		R2=0, //원래 2 
		K2=5, //원래 5 
		K1= width*K2*3/(8*(R1+R2)), //원래 50
		uping=1,
		downing=0;
	float A=0, B=0, theta_step, phi_step, z[buffer_size]; //i는 파이 진행 j는 세타 진행 A와 B는 x,z축 회전각도 진행 
    char b[buffer_size]; //화면 크기 만큼의 배열(진짜 문자가 출력되는 부분) 
    printf("\x1b[2J"); //의미 없는 부분(리눅스에서만 작동) 
    for(; ; ) {
        memset(b,' ',buffer_size); //행렬 비우기 
        memset(z,0,buffer_size * sizeof(float)); //z버퍼는 z의 좌표를 저장하는 버퍼 
        for(phi_step=0; 6.28>phi_step; phi_step+=0.02) { 
            for(theta_step=0; 6.28 >theta_step; theta_step+=0.07) {
                float sin_phi=sin(phi_step), //사인 theta
                      cos_theta=cos(theta_step), //코사인pi
                      sinA=sin(A), //사인A 
                      sin_theta=sin(theta_step), //사인pi
                      cosA=cos(A), //코사인A 
                      cos_theta2= R1*cos_theta+R2, //코사인pi+2(R2 -> y축(회전축)과의 원중심까지의 거리)(x좌표 구할때 쓰이는)
                      mess=1/(sin_phi*cos_theta2*sinA+sin_theta*cosA+K2), //1/z 
                      cos_phi=cos(phi_step), //코사인 theta 
                      cosB=cos(B), //코사인 B 
                      sinB=sin(B), //사인 B x에 					원래 30곱해줌 y에 원래 15곱해줌 구 돌릴때 3곱해주는게 베스트 
                      t=sin_phi*cos_theta2*cosA-sin_theta*sinA; //복잡함을 t로 치환 
                int x=width/2+(K1-20)*mess*(cos_phi*cos_theta2*cosB-t*sinB), //중간의 x,y좌표가 0이므로 width/2를 더해줌 
                    y= ((height/2)+1)+(K1-35)*mess*(cos_phi*cos_theta2*sinB +t*cosB), //중간의 x,y좌표가 0이므로 (height/2)+1이 height/2보다 더 자연스러움 
                     //K1-20과 K1-35를 채택한 이유: 적당한 거리를 위해 
                    idx=x+width*y, //인덱스 번호
                    N=8*((sin_theta*sinA-sin_phi*cos_theta*cosA)*cosB-sin_phi*cos_theta*sinA-sin_theta*cosA-cos_phi*cos_theta*sinB); //휘도 구하기
                if(22>y&&y>0&&x>0&&80>x&&mess>z[idx]){
				 //22>y&&y>0&&x>0&&80>x -> 화면안에 들어와있는지를 감지
				 //mess>z[idx] 현재 z버퍼에 저장되어있는 거리보다 작으면(화면에 가까우면)
				 //조건식 통과 
                    z[idx]=mess; //거리를 바꿈 
                    b[idx]=".,-~:;=!*#$@"[N>0?N:0]; //.,-~:;=!*#$@
                    //현재 char인덱스에 밝기에 따른 문자열을 저장 
                }
            }
        }
		system("cls");
        for(k=0; 1761>k; k++)
            putchar(k%80?b[k]:10); //80의 배수칸째가 될때에는 \n 즉 줄 바꿈
            //그 전까지는 b배열속 문자들 출력 
        A+=0.20; //0.04 x축 회전 
        B+=0.18; //0.02 A와 B는 2파이 넘어도 작동 -> 삼각함수의 주기성 y축 회전 
	    if(downing==1){
	    	K2-=1; //1
		}
	    else if(uping==1){
	    	K2+=1;
		}
	    if(uping==1&&K2>11){
	        uping=0;
	        downing=1;
		}
		else if(downing==1&&K2<5){
	        uping=1;
	        downing=0;
		}

    }
}
