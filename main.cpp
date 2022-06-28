#include "Sculptor.hpp"

int main() {
	Sculptor projeto(21, 8, 16);
  //Cor Branco
	projeto.setColor(0.93, 1.0, 1.0, 1.0);
  //pes
	projeto.putBox(5,7,1,3,0,6);
  projeto.putBox(5,7,5,7,0,6);
  //rabo
  projeto.putBox(18,21,2,6,5,12);
  //pes
  projeto.putBox(14,16,1,3,0,7);
  projeto.putBox(14,16,5,7,0,7);  

  
  projeto.putBox(4,9,0,8,6,14);
  projeto.putBox(9,18,1,7,7,13);

  projeto.putBox(3,4,1,3,13,15); 
  projeto.putBox(3,4,5,7,13,15); 

  //
  projeto.putBox(2,4,1,7,7,13);
  projeto.putBox(2,4,1,7,11,12);
  
  //focinho 
  projeto.setColor(0.9,0.8,0.7, 1.0);
  projeto.putBox(2,3,3,6,10,11); 
  projeto.putBox(0,2,2,6,7,10);
  projeto.setColor(0.0,0.0,0.0, 0.0); 
  projeto.putBox(0,2,2,6,7,8);
  projeto.putBox(0,1,3,5,9,10);
  projeto.setColor(0.0,0.0,0.0, 0.0);
  projeto.putBox(2,3,2,3,10,11);
  projeto.putBox(2,3,5,6,10,11);
  //coleira
  projeto.setColor(0.7,0.0,0.0,1.0);
  projeto.putBox(4,5,0,8,6,14);
  projeto.writeOFF((char*)"cachorroMinecraft.off");
	return 0;
}