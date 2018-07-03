#ifndef _KEY4X4_H_
#define _KEY4X4_H_

#define KEY4X4_port P1       //定义矩阵键盘接在哪一组IO口上

unsigned char KEY1_1=0,KEY1_2=0,KEY1_3=0,KEY1_4=0;
unsigned char KEY2_1=0,KEY2_2=0,KEY2_3=0,KEY2_4=0;
unsigned char KEY3_1=0,KEY3_2=0,KEY3_3=0,KEY3_4=0;
unsigned char KEY4_1=0,KEY4_2=0,KEY4_3=0,KEY4_4=0;

void KEY4X4_delay(int n){
	int i,j;
	for(i=0;i<n;i++){
		for(j=0;j<1000;j++);
	}	
}
/*************单键扫描****************/
unsigned char KEY4X4_scan(){
  unsigned char temp;
  unsigned char KEY4X4=0x00;
  KEY4X4_port=0xfe;
  temp=KEY4X4_port;
  temp=temp&0xf0;
  if(temp!=0xf0){
    KEY4X4_delay(10);
    temp=KEY4X4_port;
  	temp=temp&0xf0;
    if(temp!=0xf0){
      temp=KEY4X4_port;
      switch(temp){
        case 0xee:{
          KEY4X4=0x11;
          break;
        }
        case 0xde:{
          KEY4X4=0x12;
          break;
        }
        case 0xbe:{
          KEY4X4=0x13;
          break;
        }
        case 0x7e:{
          KEY4X4=0x14;
          break;
        }
        default:{
        	KEY4X4=0xff;
        	break;
        }
      }
      while(temp!=0xf0){
        temp=KEY4X4_port;
        temp=temp&0xf0;
      }
    }
  }
  KEY4X4_port=0xfd;
  temp=KEY4X4_port;
  temp=temp&0xf0;
  if(temp!=0xf0){
    KEY4X4_delay(10);
    temp=KEY4X4_port;
  	temp=temp&0xf0;
    if(temp!=0xf0){
      temp=KEY4X4_port;
      switch(temp){
        case 0xed:{
          KEY4X4=0x21;
          break;
        }
        case 0xdd:{
          KEY4X4=0x22;
          break;
        }
        case 0xbd:{
          KEY4X4=0x23;
          break;
        }
        case 0x7d:{
          KEY4X4=0x24;
          break;
        }
        default:{
        	KEY4X4=0xff;
        	break;
        }
      }
      while(temp!=0xf0){
        temp=KEY4X4_port;
        temp=temp&0xf0;
      }
    }
  }
  KEY4X4_port=0xfb;
  temp=KEY4X4_port;
  temp=temp&0xf0;
  if(temp!=0xf0){
    KEY4X4_delay(10);
    temp=KEY4X4_port;
  	temp=temp&0xf0;
    if(temp!=0xf0){
      temp=KEY4X4_port;
      switch(temp){
        case 0xeb:{
          KEY4X4=0x31;
          break;
        }
        case 0xdb:{
          KEY4X4=0x32;
          break;
        }
        case 0xbb:{
          KEY4X4=0x33;
          break;
        }
        case 0x7b:{
          KEY4X4=0x34;
          break;
        }
        default:{
        	KEY4X4=0xff;
        	break;
        }
      }
      while(temp!=0xf0){
        temp=KEY4X4_port;
        temp=temp&0xf0;
      }
    }
  }
  KEY4X4_port=0xf7;
  temp=KEY4X4_port;
  temp=temp&0xf0;
  if(temp!=0xf0){
    KEY4X4_delay(10);
    temp=KEY4X4_port;
  	temp=temp&0xf0;
    if(temp!=0xf0){
      temp=KEY4X4_port;
      switch(temp){
        case 0xe7:{
          KEY4X4=0x41;
          break;
        }
        case 0xd7:{
          KEY4X4=0x42;
          break;
        }
        case 0xb7:{
          KEY4X4=0x43;
          break;
        }
        case 0x77:{
          KEY4X4=0x44;
          break;
        }
        default:{
        	KEY4X4=0xff;
        	break;
        }
      }
      while(temp!=0xf0){
        temp=KEY4X4_port;
        temp=temp&0xf0;
      }
    }
  }
  return KEY4X4;
}

/*************多键检测****************/
void KEY4X4_many(){
  unsigned char temp;
  KEY1_1=0;KEY1_2=0;KEY1_3=0;KEY1_4=0;
	KEY2_1=0;KEY2_2=0;KEY2_3=0;KEY2_4=0;
	KEY3_1=0;KEY3_2=0;KEY3_3=0;KEY3_4=0;
	KEY4_1=0;KEY4_2=0;KEY4_3=0;KEY4_4=0;
  KEY4X4_port=0xfe;
  temp=KEY4X4_port;
  temp=temp&0xf0;
  if(temp!=0xf0){
    KEY4X4_delay(10);
    temp=KEY4X4_port;
  	temp=temp&0xf0;
    if(temp!=0xf0){
      temp=KEY4X4_port;
      temp=temp&0xf0;
      if((temp&0x10)==0x00){
      	KEY1_1=1;
      }
    	if((temp&0x20)==0x00){
    		KEY1_2=1;
    	}
    	if((temp&0x40)==0x00){
    		KEY1_3=1;
    	}
    	if((temp&0x80)==0x00){
    		KEY1_4=1;
    	}
    }
  }
  KEY4X4_delay(10);
  KEY4X4_port=0xfd;
  temp=KEY4X4_port;
  temp=temp&0xf0;
  if(temp!=0xf0){
    KEY4X4_delay(10);
    temp=KEY4X4_port;
  	temp=temp&0xf0;
    if(temp!=0xf0){
      temp=KEY4X4_port;
      temp=temp&0xf0;
      if((temp&0x10)==0x00){
      	KEY2_1=1;
      }
    	if((temp&0x20)==0x00){
    		KEY2_2=1;
    	}
    	if((temp&0x40)==0x00){
    		KEY2_3=1;
    	}
    	if((temp&0x80)==0x00){
    		KEY2_4=1;
    	}
    }
  }
  KEY4X4_delay(10);
  KEY4X4_port=0xfb;
  temp=KEY4X4_port;
  temp=temp&0xf0;
  if(temp!=0xf0){
    KEY4X4_delay(10);
    temp=KEY4X4_port;
  	temp=temp&0xf0;
    if(temp!=0xf0){
      temp=KEY4X4_port;
      temp=temp&0xf0;
      if((temp&0x10)==0x00){
      	KEY3_1=1;
      }
    	if((temp&0x20)==0x00){
    		KEY3_2=1;
    	}
    	if((temp&0x40)==0x00){
    		KEY3_3=1;
    	}
    	if((temp&0x80)==0x00){
    		KEY3_4=1;
    	}
    }
  }
  KEY4X4_delay(10);
  KEY4X4_port=0xf7;
  temp=KEY4X4_port;
  temp=temp&0xf0;
  if(temp!=0xf0){
    KEY4X4_delay(10);
    temp=KEY4X4_port;
  	temp=temp&0xf0;
    if(temp!=0xf0){
      temp=KEY4X4_port;
      temp=temp&0xf0;
      if((temp&0x10)==0x00){
      	KEY4_1=1;
      }
    	if((temp&0x20)==0x00){
    		KEY4_2=1;
    	}
    	if((temp&0x40)==0x00){
    		KEY4_3=1;
    	}
    	if((temp&0x80)==0x00){
    		KEY4_4=1;
    	}
    }
  }
}

#endif