#include <stdio.h>
#include <string.h>
#include <math.h>
#include <unistd.h>

/*K1 = 50       z' = ����� ȭ����� �Ÿ� K1 ������� 
  K2 = 5        K2�� ����� ���ӻ��� �ִ�Ÿ� 
  R1 = 1
  R2 = 2
*/

int k;
//double sin() ,cos(); //�ǹ� ���� �κ� 
main(){
    const size_t width = 80; //80
	const size_t height = 22; //22
	const size_t buffer_size = height * width; //ȭ�� ���� ũ�� : 80 ���� 22
	int R1=1, //���� 1 
		R2=0, //���� 2 
		K2=5, //���� 5 
		K1= width*K2*3/(8*(R1+R2)), //���� 50
		uping=1,
		downing=0;
	float A=0, B=0, theta_step, phi_step, z[buffer_size]; //i�� ���� ���� j�� ��Ÿ ���� A�� B�� x,z�� ȸ������ ���� 
    char b[buffer_size]; //ȭ�� ũ�� ��ŭ�� �迭(��¥ ���ڰ� ��µǴ� �κ�) 
    printf("\x1b[2J"); //�ǹ� ���� �κ�(������������ �۵�) 
    for(; ; ) {
        memset(b,' ',buffer_size); //��� ���� 
        memset(z,0,buffer_size * sizeof(float)); //z���۴� z�� ��ǥ�� �����ϴ� ���� 
        for(phi_step=0; 6.28>phi_step; phi_step+=0.02) { 
            for(theta_step=0; 6.28 >theta_step; theta_step+=0.07) {
                float sin_phi=sin(phi_step), //���� theta
                      cos_theta=cos(theta_step), //�ڻ���pi
                      sinA=sin(A), //����A 
                      sin_theta=sin(theta_step), //����pi
                      cosA=cos(A), //�ڻ���A 
                      cos_theta2= R1*cos_theta+R2, //�ڻ���pi+2(R2 -> y��(ȸ����)���� ���߽ɱ����� �Ÿ�)(x��ǥ ���Ҷ� ���̴�)
                      mess=1/(sin_phi*cos_theta2*sinA+sin_theta*cosA+K2), //1/z 
                      cos_phi=cos(phi_step), //�ڻ��� theta 
                      cosB=cos(B), //�ڻ��� B 
                      sinB=sin(B), //���� B x�� 					���� 30������ y�� ���� 15������ �� ������ 3�����ִ°� ����Ʈ 
                      t=sin_phi*cos_theta2*cosA-sin_theta*sinA; //�������� t�� ġȯ 
                int x=width/2+(K1-20)*mess*(cos_phi*cos_theta2*cosB-t*sinB), //�߰��� x,y��ǥ�� 0�̹Ƿ� width/2�� ������ 
                    y= ((height/2)+1)+(K1-35)*mess*(cos_phi*cos_theta2*sinB +t*cosB), //�߰��� x,y��ǥ�� 0�̹Ƿ� (height/2)+1�� height/2���� �� �ڿ������� 
                     //K1-20�� K1-35�� ä���� ����: ������ �Ÿ��� ���� 
                    idx=x+width*y, //�ε��� ��ȣ
                    N=8*((sin_theta*sinA-sin_phi*cos_theta*cosA)*cosB-sin_phi*cos_theta*sinA-sin_theta*cosA-cos_phi*cos_theta*sinB); //�ֵ� ���ϱ�
                if(22>y&&y>0&&x>0&&80>x&&mess>z[idx]){
				 //22>y&&y>0&&x>0&&80>x -> ȭ��ȿ� �����ִ����� ����
				 //mess>z[idx] ���� z���ۿ� ����Ǿ��ִ� �Ÿ����� ������(ȭ�鿡 ������)
				 //���ǽ� ��� 
                    z[idx]=mess; //�Ÿ��� �ٲ� 
                    b[idx]=".,-~:;=!*#$@"[N>0?N:0]; //.,-~:;=!*#$@
                    //���� char�ε����� ��⿡ ���� ���ڿ��� ���� 
                }
            }
        }
		system("cls");
        for(k=0; 1761>k; k++)
            putchar(k%80?b[k]:10); //80�� ���ĭ°�� �ɶ����� \n �� �� �ٲ�
            //�� �������� b�迭�� ���ڵ� ��� 
        A+=0.20; //0.04 x�� ȸ�� 
        B+=0.18; //0.02 A�� B�� 2���� �Ѿ �۵� -> �ﰢ�Լ��� �ֱ⼺ y�� ȸ�� 
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
