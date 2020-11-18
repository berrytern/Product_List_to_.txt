/*Implemente um controle simples de mercadorias de uma empresa qualquer. 
Para cada produto armazene um código numérico, quantidade atual e descrição. 
O programa deve ter opções para entrada, atualização da quantidade de produtos, 
relatório de produtos disponíveis e um relatório de produtos não disponíveis. 
Armazene os dados em arquivo binário. Sinalize os produtos não disponíveis com a quantidade igual a 0.*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <locale.h>
#define limit_p 5
typedef struct product{
	int id;
    char name[30];
    char desc[120];
    float price;
    int discount;
    int quant;
    bool active;
} tipo_product;

tipo_product list_product[limit_p];

void create_product(tipo_product *l){
	
		
}
bool insert(tipo_product *add){
	int i;
	bool added=false;
	for(i=0; i<limit_p;i++){
		if(list_product[i].active==false){
			strcpy(list_product[i].name, (*add).name);
			list_product[i].price=(*add).price;
			strcpy(list_product[i].desc, (*add).desc);
			list_product[i].discount=(*add).discount;
			list_product[i].quant=(*add).quant;
			list_product[i].active=(*add).active;
			added=true;
			break;
		}
	}
	return added;
}
int alter(int id,tipo_product change){
	int i;
	for(i=0;i<limit_p;i++){
		if(list_product[i].active==true && list_product[i].id==id){
			//strcpy(list_product[i].name, change.name);
			list_product[i].price=change.price;
			list_product[i].discount=change.discount;
			strcpy(list_product[i].desc, change.desc);
			list_product[i].quant=change.quant;
			return 1;
		}
	}
	return 0;
}
void listar(int beggin,int end){
	int i;
	if(end>limit_p|| beggin>end || end<0){
		end=limit_p;
	}
	if(beggin<0){
		beggin=0;
	}
	for(i=beggin;i<end;i++){
		if(list_product[i].active==true){
			printf("{\nid: %d\n",list_product[i].id);
			printf("nome: %s\n",list_product[i].name);
			printf("preço: %.2f\n",list_product[i].price);
			printf("descrição: %s\n",list_product[i].desc);
			printf("desconto: %d %%\n",list_product[i].discount);
			printf("quantidade: %d\n",list_product[i].quant);
			printf("},\n");
		}
	}
}
int query_list(int option,char ask[]){
	if(option==1){
		printf("------- Criação de produtos -------\n");
	}else if(option==2){
		printf("------- Listagem de produtos -------\n");
	}else if(option==3){
		printf("------- Alteração de produtos -------\n");
	}
	printf("\n%s?\n",ask);
	printf("\n0 - Não\n");
	printf("1 - Sim\n");
	printf("\nescolha: ");
}
int exists(int id){
	int i;
	for(i=0;i<limit_p;i++){
		if(list_product[i].active==true && list_product[i].id==id){
			return 1;
		}
	}
	return 0;
}
int main(){
	setlocale(LC_ALL, "");
	int run=1;
	int option;
	int i=0;
	for(i=0;i<limit_p;i++){
		strcpy(list_product[i].name, "");
		list_product[i].id=i;
		list_product[i].price=0; 
		list_product[i].discount=0;
		strcpy(list_product[i].desc,"");
		list_product[i].quant=0;
		list_product[i].active=false;
	}
	while(run==1){
		system("cls");
		int not_stay;
		printf("------- Menu -------\n");
		printf("\n0 - criar um produto\n");
		printf("1 - alterar\n");
		printf("2 - listar produtos\n");
		printf("3 - salvar em arquivo.txt\n");
		printf("\nescolha a opção: ");
		scanf("%d",&option);
		fflush(stdin);
		while(option==0){
			char name[30];
			float price;
			char desc[120];
			int discount;
			int quant;
			system("cls");
			printf("------- Criação de produtos -------\n");
			printf("\nO produto tem nome,preço e desconto\n");
			printf("\ninsira o nome: ");
			scanf("%s",&name);
			fflush(stdin);
			printf("\ninsira o preço(com vírgula): ");
			scanf("%f",&price);
			fflush(stdin);
			printf("\ninsira o descrição: ");
				scanf("%47[,0-9a-zA-Z ]",&desc);
			fflush(stdin);
			printf("\ninsira o desconto em %%: ");
			scanf("%d",&discount);
			fflush(stdin);
			printf("\ninsira a quantidade: ");
			scanf("%d",&quant);
			fflush(stdin);
			tipo_product add;
			strcpy(add.name, name);
			add.price=price;
			strcpy(add.desc, desc);
			add.discount=discount;
			add.quant=quant;
			add.active=true;
			printf("\nstatus: ");
			if(insert(&add)){
				printf("inserido\n");
			}
			else{
				printf("error ao inserir\n");
			}
			query_list(0,"criar outro produto");
			scanf("%d",&not_stay);
			fflush(stdin);
			if(not_stay==0){
				option=-1;
			}
		}
		while(option==1){
			int exist=0;
			int id;
			float price;
			int discount;
			char desc[120];
			int quant;
			int res=1;
			while(exist==0){
				system("cls");
				printf("------- Alteração de produtos -------\n");
				printf("\nid do produto: ");
				scanf("%d",&id);
				fflush(stdin);
				exist=exists(id);
				if(!exist){
					system("cls");
					query_list(3,"não encontrado!\ntentar novamente?");
					scanf("%d",&res);
					fflush(stdin);
					if(!res){
						exist=1;
						option=-1;
					}
					
				}
			}
			if(res==1){
				printf("\ninsira o novo preço: ");
				scanf("%f",&price);
				fflush(stdin);
				printf("%f", price);
				printf("\ninsira a nova descrição: ");
				scanf("%47[,0-9a-zA-Z ]",&desc);
				fflush(stdin);
				printf("\ninsira o novo desconto em %: ");
				scanf("%d",&discount);
				fflush(stdin);
				printf("\ninsira a nova quantidade: ");
				scanf("%d",&quant);
				fflush(stdin);
				tipo_product change;
				strcpy(change.name, "any");
				change.price=price;
				strcpy(change.desc, desc);
				change.discount=discount;
				change.quant=quant;
				change.active=true;
				alter(id,change);
				query_list(0,"alterar outro produto");
				scanf("%d",&not_stay);
				fflush(stdin);
				if(not_stay==0){
					option=-1;
				}
			}
		}
		while(option==2){
			int p_option=-1;
			int beggin=-1;
			int end=-1;
			while(p_option==-1){
				system("cls");
				query_list(2,"quer listar do inicio");
				scanf("%d",&p_option);
				fflush(stdin);
				if(p_option==0){
					printf("\nquer pular quantos produtos?: ");
					scanf("%d",&beggin);
					fflush(stdin);
				}
				system("cls");
				query_list(2,"quer listar até o fim da lista?");
				scanf("%d",&p_option);
				fflush(stdin);
				if(p_option==0){
					printf("\nquer listar quantos produtos?: ");
					scanf("%d",&end);
					fflush(stdin);
				}
				system("cls");
			}
			printf("Produtos: \n");
			listar(beggin,end);
			printf("insira algo para continuar");
			scanf("%s",&p_option);
			system("cls");
			query_list(2,"listar novamente");
			scanf("%d",&not_stay);
			fflush(stdin);
			if(not_stay==0){
				option=-1;
			}
		}
		if(option==3){
			run=0;
			FILE *f = fopen("products.txt", "w");
			if (f == NULL){
			    printf("Error opening file!\n");
			    exit(1);
			}else{
				int i=0;
				for(i=0;i<limit_p;i++){
					if(list_product[i].active==true){
						fprintf(f,"{\nid: %d\n",list_product[i].id);
						fprintf(f,"nome: %s\n",list_product[i].name);
						fprintf(f,"preço: %.2f\n",list_product[i].price);
						fprintf(f,"descrição: %s %\n",list_product[i].desc);
						fprintf(f,"desconto: %d %\n",list_product[i].discount);
						fprintf(f,"quantidade: %d %\n",list_product[i].quant);
						fprintf(f,"},\n");
					}
				}
				printf("\nSalvo!!!\n");
			}
			fclose(f);
		}
	}
	
	
	return 0;
}


