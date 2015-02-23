#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <stdbool.h>
#include <time.h>
using namespace std;

const int LARGURA_TELA = 30*24;
const int ALTURA_TELA = 30*24;
const int cte=80;
int matriz[20][10]= {{0}};
int prox=0, hold=0, atual=0, lim=0, t=0, mov=0, pontuacao=0, record = 0, fase=1, linha=0;
#include "pecas.h"
peca *p=NULL;

ALLEGRO_BITMAP *quadro[10], *nome[10], *numero[11];
ALLEGRO_BITMAP *objeto[8];
ALLEGRO_DISPLAY *janela = NULL;
ALLEGRO_EVENT_QUEUE *fila_eventos = NULL;
ALLEGRO_TIMER *timer = NULL;

bool sair = false, pause=false, end_game=false, invisible=false;
bool inicializar();
bool carregarArquivos();
void finalizar();
void imprimir();
peca *NOVA(int i)//Gera nova peça
{
    peca *a;
    switch(i)
    {
    case 1:
        a=new O_peca ;
        break;
    case 2:
        a=new J_peca;
        break;
    case 3:
        a=new I_peca;
        break;
    case 4:
        a=new L_peca;
        break;
    case 5:
        a=new Z_peca;
        break;
    case 6:
        a=new S_peca;
        break;
    case 7:
        a=new T_peca;
        break;
    }
    return a;
}
void HOLD()
{
    if(lim==0)//Se ainda nao tiver trocado a peça
    {
        p->APAGA();//Exclui a peça atual
        delete p;
        if(hold==0)//Se estiver vazio, guarda peça e puxa a proxima
        {
            hold=atual;
            atual=prox;
            prox=rand()%7+1;
        }
        else//Se não, troca as duas peças
        {
            int aux;
            aux=hold;
            hold=atual;
            atual=aux;
        }
        p=NOVA(atual);//Gera a peça nova
        lim=1;
    }
}
void DELETE_LINHA(int n)//Exclui linha de ordem n
{
    linha++;
    if(linha>=5*(fase+1)*fase/2)
        fase++;
    int i, j;
    for(j=4; j>=0; j--)//
    {
        matriz[n][j]=0;
        matriz[n][9-j]=0;
        imprimir();
        al_rest(0.05);
    }
    for(j=0; j<10; j++)//
    {
        for(i=n; i>0; i--)//Faz cada quadro ser o de cima
        {
            matriz[i][j]=matriz[i-1][j];
        }
        matriz[i][j]=0;//Torna o quadro superior vazio
    }
}
int QUEDA()// Quando a peça cai, verifica as linhas e se o jogo foi perdido
{
    int cont=0;// conta as linhas tiradas na jogada
    int v=0;//conta os bloquinhos preenchidos em cada linha;
    for(int i=19; i>0; i--)
    {
        v=0;
        for(int j=0; j<10; j++)
        {
            if(matriz[i][j])
                v++;
            if(v==10)
            {
                DELETE_LINHA(i);
                j=-1;
                v=0;
                cont++;
            }
        }

    }
    if(cont)
    {
        switch(cont)//Pontua o jogo de acordo com o combo
        {
        case 1:
            pontuacao+=1;
            break;
        case 2:
            pontuacao+=3;
            break;
        case 3:
            pontuacao+=5;
            break;
        case 4:
            pontuacao+=8;
            break;
        }
        if(pontuacao>record)
        {
            record=pontuacao;
            ofstream escrita("record.txt");
            if(escrita)
            {
                escrita << record;
                escrita.close();
            }
            else cout << "erro ao abrir arquivo";

        }

    }
    if(p->lost())//Verifica se o jogo foi perdido(valor de retorno)
    {
        return 1;
    }
    delete p;
    p= NOVA(prox);
    atual=prox;
    prox=rand()%7+1;
    lim=0;
    return 0;
}
void NEW_GAME()
{
    for(int i=0; i<20; i++)
        for(int j=0; j<10; j++)
            matriz[i][j]=0;
    fase=1;
    linha=0;
    pontuacao=0;
    pause=false;
    end_game=false;
    hold = 0;
    al_rest(0.1);
    prox=rand()%7+1;
    p = NOVA(prox);
    atual=prox;
    prox=rand()%7+1;
    imprimir();
}
int main(void)
{
    ifstream leitura ("record.txt");
    if(leitura)
    {
        leitura >> record;
        leitura.close();
    }

    int tecla=0;
    srand((unsigned)time(NULL));
    if (!inicializar())
    {
        return -1;
    }
    if (!carregarArquivos())
    {
        return -1;
    }

    al_start_timer(timer);

    NEW_GAME();

    while(!sair)
    {
        if (!al_is_event_queue_empty(fila_eventos))
        {
            ALLEGRO_EVENT evento;
            al_wait_for_event(fila_eventos, &evento);
            if(!end_game)
            {
                if(!pause)
                {
                    if (evento.type == ALLEGRO_EVENT_TIMER)
                    {
                        t++;
                        mov++;
                        if(t>=cte/fase)
                        {
                            if(p->DOWN())
                            {
                                if(QUEDA())
                                    end_game=true;
                            }
                            imprimir();
                            t=0;
                        }

                    }
                    else if (evento.type == ALLEGRO_EVENT_KEY_DOWN)
                    {
                        switch(evento.keyboard.keycode)
                        {
                        case ALLEGRO_KEY_UP:
                            tecla=1;
                            break;
                        case ALLEGRO_KEY_DOWN:
                            tecla=2;
                            break;
                        case ALLEGRO_KEY_LEFT:
                            tecla=3;
                            mov=0;
                            break;
                        case ALLEGRO_KEY_RIGHT:
                            mov=0;
                            tecla=4;
                            break;
                        case ALLEGRO_KEY_C:
                            tecla=5;
                            break;
                        case ALLEGRO_KEY_SPACE:
                            tecla=6;
                            break;
                        case ALLEGRO_KEY_P:
                            tecla=7;
                        }
                    }
                    else if (evento.type == ALLEGRO_EVENT_KEY_CHAR)
                    {
                        if(p->verifica()&&mov>3)
                            switch(evento.keyboard.keycode)
                            {
                            case ALLEGRO_KEY_DOWN:
                                tecla=2;
                                break;
                            case ALLEGRO_KEY_LEFT:
                                tecla=3;
                                break;
                            case ALLEGRO_KEY_RIGHT:
                                tecla=4;
                                break;
                            }
                    }
                }
                else if (evento.type == ALLEGRO_EVENT_KEY_DOWN)
                {
                    if(evento.keyboard.keycode==ALLEGRO_KEY_P)
                    {
                        tecla =7;
                    }

                }
                else if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
                {
                    if (evento.mouse.x >= 240 &&
                            evento.mouse.x <= 360 && evento.mouse.y >= 270 &&
                            evento.mouse.y <=330)
                        pause=false;
                    else if(evento.mouse.x >= 225 &&
                            evento.mouse.x <= 375 && evento.mouse.y >= 270+90&&
                            evento.mouse.y <=330+90)
                        NEW_GAME();
                    else if (evento.mouse.x >= 255 &&
                             evento.mouse.x <= 345 && evento.mouse.y >= 270+180 &&
                             evento.mouse.y <=330+180 )
                        sair=true;
                }
            }
            else if (evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)
            {
                if (evento.mouse.x >= 225 &&
                        evento.mouse.x <= 375 && evento.mouse.y >= 270+60 &&
                        evento.mouse.y <=330+60)
                    NEW_GAME();
                else if (evento.mouse.x >= 255 &&
                         evento.mouse.x <= 345 && evento.mouse.y >= 420 &&
                         evento.mouse.y <=420+60 )
                    sair=true;
            }
            if (evento.type == ALLEGRO_EVENT_DISPLAY_CLOSE)
            {
                sair = true;
            }
            else if(tecla)
            {
                switch(tecla)
                {
                case 1:
                    p->GIRAR();
                    break;
                case 2:
                    if(p->DOWN())
                        if(QUEDA())
                            end_game=true;
                    break;
                case 3:
                    p->LEFT();
                    break;
                case 4:
                    p->RIGHT();
                    break;
                case 5:
                    HOLD();
                    break;
                case 6:
                    while(!p->DOWN());
                    if(QUEDA())
                        end_game=true;
                    break;
                case 7:
                    if (pause==true)
                        pause=false;
                    else
                        pause=true;
                    break;
                }
                tecla=0;
            }
            else if(evento.type == ALLEGRO_EVENT_MOUSE_BUTTON_UP)//Se houver click no botão do canto direito, alterna o modo;
			{
				if (evento.mouse.x >= 22*30 &&
                        evento.mouse.x <= 23*30 && evento.mouse.y >= 30 &&
                        evento.mouse.y <= 60)
						if(invisible==true)
							invisible=false;
						else
							invisible=true;
			}
                imprimir();
        }
    }
    finalizar();
    return 0;
}
bool inicializar()
{
    if (!al_init())
    {
        cout << "Falha ao iniciar Allegro." << endl;
        return false;
    }

    if (!al_init_image_addon())
    {
        cout << "Falha ao iniciar allegro_image." << endl;
        return false;
    }
    if (!al_install_keyboard())
    {
        cout << "Falha ao inicializar teclado.\n";
        return false;
    }

    janela = al_create_display(LARGURA_TELA, ALTURA_TELA);
    if (!janela)
    {
        cout << "Falha ao criar a janela.\n";
        return false;
    }

    al_set_window_title(janela, "Tetris");

    fila_eventos = al_create_event_queue();
    if (!fila_eventos)
    {
        cout << "Falha ao criar fila de eventos.\n";
        return false;
    }
    timer = al_create_timer(0.01);
    if (!timer)
    {
        cout << "Falha ao criar timer.\n";
        al_destroy_event_queue(fila_eventos);
        al_destroy_display(janela);
        return false;
    }
    if (!al_install_mouse())
    {
        fprintf(stderr, "Falha ao inicializar o mouse.\n");
        al_destroy_display(janela);
        return -1;
    }
    if (!al_set_system_mouse_cursor(janela, ALLEGRO_SYSTEM_MOUSE_CURSOR_DEFAULT))
    {
        fprintf(stderr, "Falha ao atribuir ponteiro do mouse.\n");
        al_destroy_display(janela);
        return -1;
    }
    al_register_event_source(fila_eventos, al_get_keyboard_event_source());
    al_register_event_source(fila_eventos, al_get_display_event_source(janela));
    al_register_event_source(fila_eventos, al_get_mouse_event_source());
    al_register_event_source(fila_eventos, al_get_timer_event_source(timer));


    return true;
}
bool carregarArquivos()
{
    {
        char imagem[10]="img__.png";
        for(int i=0; i<10; i++)
        {
            imagem[4]=i+48;
            quadro[i] = al_load_bitmap(imagem);
            if (!quadro[i])
            {
                cout << "Falha ao carregar imagem.\n";
                return false;
            }
        }
    }
    {
        char imagem[10]="obj__.png";
        for(int i=0; i<8; i++)
        {
            imagem[4]=i+48;
            objeto[i] = al_load_bitmap(imagem);
            if (!objeto[i])
            {
                cout << "Falha ao carregar imagem.\n" << i;
                return false;
            }
        }
    }
    {
        char imagem[10]="num__.png";
        for(int i=0; i<10; i++)
        {
            imagem[4]=i+48;
            numero[i] = al_load_bitmap(imagem);
            if (!numero[i])
            {
                cout << "Falha ao carregar imagem.\n" << i;
                return false;
            }
        }
    }
    numero[10] = al_load_bitmap("num_10.png");
    if (!numero[10])
    {
        cout << "Falha ao carregar imagem.\n";
        return false;
    }

    nome[0] = al_load_bitmap("tetris.png");
    if (!nome[0])
    {
        cout << "Falha ao carregar imagem.\n";
        return false;
    }
    nome[1] = al_load_bitmap("hold.png");
    if (!nome[1])
    {
        cout << "Falha ao carregar imagem.\n";
        return false;
    }
    nome[2] = al_load_bitmap("next.png");
    if (!nome[2])
    {
        cout << "Falha ao carregar imagem.\n";
        return false;
    }
    nome[3] = al_load_bitmap("score.png");
    if (!nome[3])
    {
        cout << "Falha ao carregar imagem.\n";
        return false;
    }
    nome[4] = al_load_bitmap("pause.png");
    if (!nome[4])
    {
        cout << "Falha ao carregar imagem.\n";
        return false;
    }
    nome[5] = al_load_bitmap("end_game.png");
    if (!nome[5])
    {
        cout << "Falha ao carregar imagem.\n";
        return false;
    }
    nome[6] = al_load_bitmap("best.png");
    if (!nome[6])
    {
        cout << "Falha ao carregar imagem.\n";
        return false;
    }
    nome[7] = al_load_bitmap("level.png");
    if (!nome[7])
    {
        cout << "Falha ao carregar imagem.\n";
        return false;
    }
    nome[8] = al_load_bitmap("goal.png");
    if (!nome[8])
    {
        cout << "Falha ao carregar imagem.\n";
        return false;
    }

    return true;
}
void finalizar()
{
    for(int i=0; i<10; i++)
        al_destroy_bitmap(quadro[i]);
    al_destroy_timer(timer);
    al_destroy_event_queue(fila_eventos);
    al_destroy_display(janela);
}
void imprimir()
{
    for(int i=0; i<24; i++)//coloca quadros cinza em toda a tela
        for(int j=0; j<24; j++)
            al_draw_bitmap(quadro[9], j*30, i*30, 0);

    al_draw_bitmap(nome[0], 150, 0, 0);//Nome tetris
    al_draw_bitmap(nome[1], 30, 150, 0);//Nome hold
    al_draw_bitmap(objeto[hold], 30, 180, 0); //Hold
    al_draw_bitmap(nome[2], 540, 150, 0);//Nome next
    al_draw_bitmap(objeto[prox], 540, 180, 0);//Next
    al_draw_bitmap(nome[7], 1*30, 30*18, 0);//Nome fase
    {
        // fase
        al_draw_bitmap(numero[10], 1*30, (19)*30, 0);
        al_draw_bitmap(quadro[9], 120, 19*30, 0);
        stringstream aux;
        string pt;
        aux << fase;
        pt=aux.str();
        int n;
        for(n=0; pt[n]!='\0'; n++);
        for(int i =(n%2==1)? n/2 : n/2-1, j=1; i>=0; i--, j++)
            al_draw_bitmap(numero[pt[i]-48], 2*30+15 - j*15, 19*30, 0);
        for(int i =(n%2==1)? n/2+1 : n/2, j=0; i<n; i++, j++)
            al_draw_bitmap(numero[pt[i]-48], 2*30+15 + j*15, 19*30, 0);
    }
    al_draw_bitmap(nome[8], 1*30, 30*15, 0);//Nome goal
    {
        // goal
        al_draw_bitmap(numero[10], 1*30, (16)*30, 0);
        al_draw_bitmap(quadro[9], 120, 16*30, 0);
        stringstream aux;
        string pt;
        aux << (5*(fase+1)*fase/2-linha);
        pt=aux.str();
        int n;
        for(n=0; pt[n]!='\0'; n++);
        for(int i =(n%2==1)? n/2 : n/2-1, j=1; i>=0; i--, j++)
            al_draw_bitmap(numero[pt[i]-48], 2*30+15 - j*15, 16*30, 0);
        for(int i =(n%2==1)? n/2+1 : n/2, j=0; i<n; i++, j++)
            al_draw_bitmap(numero[pt[i]-48], 2*30+15 + j*15, 16*30, 0);
    }
    al_draw_bitmap(nome[3], 18*30, 30*18, 0);//Nome score
    {
        // score
        al_draw_bitmap(numero[10], 16*30, (19)*30, 0);
        stringstream aux;
        string pt;
        aux << pontuacao;
        pt=aux.str();
        int n;
        for(n=0; pt[n]!='\0'; n++);
        for(int i =(n%2==1)? n/2 : n/2-1, j=1; i>=0; i--, j++)
            al_draw_bitmap(numero[pt[i]-48], 19*30+15 - j*15, 19*30, 0);
        for(int i =(n%2==1)? n/2+1 : n/2, j=0; i<n; i++, j++)
            al_draw_bitmap(numero[pt[i]-48], 19*30+15 + j*15, 19*30, 0);
    }
    al_draw_bitmap(nome[6],18*30, 30*15, 0 );// Nome best
    {
        //record
        al_draw_bitmap(numero[10], 16*30, (16)*30, 0);
        stringstream aux;
        string pt;
        aux << record;
        pt=aux.str();
        int n;
        for(n=0; pt[n]!='\0'; n++);
        for(int i =(n%2==1)? n/2 : n/2-1, j=1; i>=0; i--, j++)
            al_draw_bitmap(numero[pt[i]-48], 19*30+15 - j*15, 16*30, 0);
        for(int i =(n%2==1)? n/2+1 : n/2, j=0; i<n; i++, j++)
            al_draw_bitmap(numero[pt[i]-48], 19*30+15 + j*15, 16*30, 0);
    }

    for(int i=0; i<20; i++)//coloca quadros das determinadas cores dos quadros da matriz
        for(int j=0; j<10; j++)
            if(!invisible)
                al_draw_bitmap(quadro[matriz[i][j]], 150+j*30, 90+i*30, 0);
            else
                al_draw_bitmap(quadro[0], 150+j*30, 90+i*30, 0);



    if(pause)//Pause menu
        al_draw_bitmap(nome[4], 180, 180, 0);
    if(end_game)//End game menu
        al_draw_bitmap(nome[5], 180, 180, 0);
    if(!invisible)
        al_draw_bitmap(quadro[7], 22*30, 30, 0);
    else
        {
            al_draw_bitmap(quadro[4], 22*30, 30, 0);
            for(int i=0; i<4; i++)
                if(p->q[i].y>=0)
                al_draw_bitmap(quadro[matriz[p->q[i].y][p->q[i].x]], 150+(p->q[i].x)*30, 90+(p->q[i].y)*30, 0);
        }

    al_flip_display();
}
