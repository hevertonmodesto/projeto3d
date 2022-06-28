#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cmath>
#include <queue>
#include <vector>
#include "Sculptor.hpp"

using namespace std;

Sculptor::Sculptor(int _nx, int _ny, int _nz) {
	nx = _nx;
	ny = _ny;
	nz = _nz;

	v = new Voxel **[nx]; // Alocação dinâmica de memória

	for (int i = 0; i < nx; i++) {
		v[i] = new Voxel *[ny];
	}

	for (int i = 0; i < nx; i++) {
		for (int j = 0; j < ny; j++) {
			v[i][j] = new Voxel[nz];

		}
	}

	for (int i = 0; i < nx; i++) { // Laço de repetição para atribuir valor inicial para todos os voxels
		for (int j = 0; j < ny; j++) {
			for (int k = 0; k < nz; k++) {
				v[i][j][k].isOn = false;
				v[i][j][k].r = 0;
				v[i][j][k].g = 0;
				v[i][j][k].b = 0;
				v[i][j][k].a = 0;
			}
		}
	}
}

Sculptor::~Sculptor() {

	for (int i = 0; i < nx; i++) { // Liberando as memórias, análogo ao free() da linguagem C
		for (int j = 0; j < ny; j++) {
			delete[] v[i][j];
		}
	}
	for (int i = 0; i < nx; i++) {
		delete[] v[i];
	}
	delete[] v;
}
void Sculptor::setColor(float _r, float _g, float _b, float _a){
    r = _r;//componente correspondente à cor vermelha.
    g = _g;//componente correspondente à cor verde.
    b = _b;//componente correspondente à cor azul.
    a = _a;//componente correspondente à opacidade.
}
void Sculptor::cutVoxel(int x0, int y0, int z0){
    v[x0][y0][z0].isOn = false; //o voxel não será exibido no escultor.
}
void Sculptor::putVoxel(int x0, int y0, int z0){
    v[x0][y0][z0].isOn = true;//o voxel será exibido no escultor.
    v[x0][y0][z0].r = r;
    v[x0][y0][z0].g = g;
    v[x0][y0][z0].b = b;
    v[x0][y0][z0].a = a;
}
void Sculptor::putBox(int x0, int x1, int y0, int y1, int z0, int z1){

    for (int i = x0; i < x1; i++){
        for (int j = y0; j < y1; j++){
            for (int k = z0; k < z1; k++){

    v[i][j][k].isOn = true;
    v[i][j][k].r = r;
    v[i][j][k].g = g;
    v[i][j][k].b = b;
    v[i][j][k].a = a;
            }
        }
    }

}
void Sculptor::cutBox(int x0, int x1, int y0, int y1, int z0, int z1){
    for (int i = x0; i < x1; i++){
        for (int j = y0; j < y1; j++){
            for (int k = z0; k < z1; k++){

    v[i][j][k].isOn = false;

            }
        }
    }
}
void Sculptor::putEllipsoid (int x0, int y0, int z0, int rx, int ry, int rz){
    double dx, dy, dz;
    for (int i = 0; i < nx; i++){
        for (int j = 0; j < ny; j++){
            for (int k = 0; k < nz; k++){
            dx = ((double)(i-x0)*(double)(i-x0))/(rx*rx);
            dy = ((double)(j-y0)*(double)(j-y0))/(ry*ry);
            dz = ((double)(k-z0)*(double)(k-z0))/(rz*rz);
// Condição que verifica se a equação do elipsoid é respeitada e posteriormente habilita a presença de um Voxel no local, caso ela seja respeitada.
            if ((dx + dy + dz) < 1){
                v[i][j][k].isOn = true;
                v[i][j][k].r = r;
                v[i][j][k].g = g;
                v[i][j][k].b = b;
                v[i][j][k].a = a;

            }
            }
        }
    }
}
void Sculptor::cutEllipsoid (int x0, int y0, int z0, int rx, int ry, int rz){
    double dx, dy, dz;
    for (int i = 0; i < nx; i++){
        for (int j = 0; j < ny; j++){
            for (int k = 0; k < nz; k++){
            dx = ((double)(i-x0)*(double)(i-x0))/(rx*rx);
            dy = ((double)(j-y0)*(double)(j-y0))/(ry*ry);
            dz = ((double)(k-z0)*(double)(k-z0))/(rz*rz);
              // Condição que verifica se a equação do elipsoid é respeitada e posteriormente habilita a retirada de um Voxel no local, caso ela seja respeitada.
            if ((dx + dy + dz) < 1){
                v[i][j][k].isOn = false;

            }
            }
        }
    }
}
void Sculptor::putSphere(int x0, int y0, int z0, int r){
double dx, dy, dz;
for (int i = 0; i < nx; i++){
        for (int j = 0; j < ny; j++){
            for (int k = 0; k < nz; k++){//Caso a distância seja menor que 1, isso significa que a equação é respeitada e os valores são coerentes, portanto é habilitada a presença de um Voxel no local.
            dx = ((double)(i-x0)*(double)(i-x0));
            dy = ((double)(j-y0)*(double)(j-y0));
            dz = ((double)(k-z0)*(double)(k-z0));

            if ((dx + dy + dz) < (r*r)){
            v[i][j][k].isOn = true;
            v[i][j][k].r = r;
            v[i][j][k].g = g;
            v[i][j][k].b = b;
            v[i][j][k].a = a;

            }
            }
        }
}
}
void Sculptor::cutSphere(int x0, int y0, int z0, int r){//Seguindo a mesma lógica do putSphere, porém agora ao invés de chamar putVoxel será chamado a função cutVoxel, para retirar um voxel.
double dx, dy, dz;
for (int i = 0; i < nx; i++){
        for (int j = 0; j < ny; j++){
            for (int k = 0; k < nz; k++){
            dx = ((double)(i-x0)*(double)(i-x0));
            dy = ((double)(j-y0)*(double)(j-y0));
            dz = ((double)(k-z0)*(double)(k-z0));

            if ((dx + dy + dz) < (r*r)){
            v[i][j][k].isOn = false;

            }
            }
        }
}
}

void Sculptor::writeOFF(char* filename) {
	ofstream outFile;
	outFile.open(filename);

	int qntdVoxel = 0;

	for (int i = 0; i < nx; i++) { // Conta quantos voxels tem na escultura
		for (int j = 0; j < ny; j++) {
			for (int k = 0; k < nz; k++) {
				if (v[i][j][k].isOn) {
					qntdVoxel++;
				}
			}
		}
	}

	outFile << "OFF" << endl << qntdVoxel * 8 << " " << qntdVoxel * 6 << " " << 0 << endl; // Determina o número de vértices e faces da escultura


	for (int i = 0; i < nx; i++) { // Determina as coordenadas centrais de cada voxel
		for (int j = 0; j < ny; j++) {
			for (int k = 0; k < nz; k++) {
				if (v[i][j][k].isOn) {
					outFile << i - 0.5 << " " << j + 0.5 << " " << k - 0.5 << endl;
					outFile << i - 0.5 << " " << j - 0.5 << " " << k - 0.5 << endl;
					outFile << i + 0.5 << " " << j - 0.5 << " " << k - 0.5 << endl;
					outFile << i + 0.5 << " " << j + 0.5 << " " << k - 0.5 << endl;
					outFile << i - 0.5 << " " << j + 0.5 << " " << k + 0.5 << endl;
					outFile << i - 0.5 << " " << j - 0.5 << " " << k + 0.5 << endl;
					outFile << i + 0.5 << " " << j - 0.5 << " " << k + 0.5 << endl;
					outFile << i + 0.5 << " " << j + 0.5 << " " << k + 0.5 << endl;
				}
			}
		}
	}

	int vertice = 0;
	outFile << setiosflags(ios::fixed); // Fixa a saida das cores em decimal float <iomanip>

	for (int i = 0; i < nx; i++) { // Atribuindo as faces através dos vértices
		for (int j = 0; j < ny; j++) {
			for (int k = 0; k < nz; k++) {
				if (v[i][j][k].isOn) {
					outFile << 4 << " " << vertice + 0 << " " << vertice + 3 << " " << vertice + 2 << " " << vertice + 1 << " " << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << endl;
					outFile << 4 << " " << vertice + 4 << " " << vertice + 5 << " " << vertice + 6 << " " << vertice + 7 << " " << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << endl;
					outFile << 4 << " " << vertice + 0 << " " << vertice + 1 << " " << vertice + 5 << " " << vertice + 4 << " " << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << endl;
					outFile << 4 << " " << vertice + 0 << " " << vertice + 4 << " " << vertice + 7 << " " << vertice + 3 << " " << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << endl;
					outFile << 4 << " " << vertice + 3 << " " << vertice + 7 << " " << vertice + 6 << " " << vertice + 2 << " " << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << endl;
					outFile << 4 << " " << vertice + 1 << " " << vertice + 2 << " " << vertice + 6 << " " << vertice + 5 << " " << v[i][j][k].r << " " << v[i][j][k].g << " " << v[i][j][k].b << " " << v[i][j][k].a << endl;
					vertice = vertice + 8;
				}
			}
		}
	}
	outFile.close();
}