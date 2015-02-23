class qdr
{
public:
    int x;
    int y;
    qdr (void) {}
    qdr (int a, int b)
    {
        x=a;
        y=b;
    }
    void define(int a, int b)//Escolhe os valores de x e y
    {
        x=a;
        y=b;
    }
    qdr UP (void)//Retorna o quadro de cima
    {
        qdr a(x,y-1);
        return a;
    }
    qdr DOWN (void)//Retorna o quadro de baixo
    {
        qdr a(x,y+1);
        return a;
    }
    qdr LEFT (void)
    {
        qdr a(x-1,y);
        return a;
    }
    qdr RIGHT (void)
    {
        qdr a(x+1,y);
        return a;
    }
};
class sombra
{
	qdr q[4];
	public:
	void ATUALIZAR(qdr r[4])
	{
		APAGA();
		FORMAR(r);
	}
	void FORMAR(qdr r[4])
	{
		for(int i=0;i<4;i++)
		{
			q[i].x=r[i].x;
			q[i].y=r[i].y;
		}
		while(!DOWN());
	}
	int verifica()
    {
        int aux=0;
        for(int i=0; i<4; i++)
        {
            if(q[i].y>19||q[i].x<0||q[i].x>9)
                    aux++;
            if(q[i].y>0)
            {

                if(matriz[q[i].y][q[i].x]>0&&matriz[q[i].y][q[i].x]<10)
                    aux++;
            }
        }
        return aux;
    }
    int DOWN()
    {
        int aux=0;
        APAGA();
        for(int i=0; i<4; i++)
            q[i]=q[i].DOWN();
        if(verifica())
        {
            for(int i=0; i<4; i++)
                q[i]=q[i].UP();
            aux++;
        }
        COLOR();
        return aux;
    }
	void APAGA()
    {
        for(int i=0; i<4; i++)
            if(q[i].y>=0&&q[i].y<20&&q[i].x>=0&&q[i].x<10)
                if(matriz[q[i].y][q[i].x]==8)
					matriz[q[i].y][q[i].x]=0;
    }
	void COLOR()
    {
        for(int i=0; i<4; i++)
            if(q[i].y>=0)
					if(matriz[q[i].y][q[i].x]==0)
						matriz[q[i].y][q[i].x]=8;
    }
};
class peca
{
protected:
    int cor;
    int posicao; int n_posicao;
    sombra s;
public:
	qdr q[4];
    peca(int a=0, int b=4)
    {
        cor=a;
        n_posicao=b;
    }
    int verifica()
    {
        int aux=0;
        for(int i=0; i<4; i++)
        {
            if(q[i].y>19||q[i].x<0||q[i].x>9)
                    aux++;
            if(q[i].y>0)
            {
                if(matriz[q[i].y][q[i].x]>0&&matriz[q[i].y][q[i].x]<8)
                    aux++;
            }
        }
        return aux;
    }
    int lost()
    {
        int aux=0;
        for(int i=0; i<4; i++)
        {
            if(q[i].y<0)
                aux++;
        }
        return aux;
    }
    void UP()
    {
        APAGA();
        for(int i=0; i<4; i++)
            q[i]=q[i].UP();
        if(verifica())
            for(int i=0; i<4; i++)
                q[i]=q[i].DOWN();//Se tiver peça atraz, faz o movimento inverso.
        COLOR();
    }
    int DOWN()
    {
        int aux=0;
        APAGA();
        for(int i=0; i<4; i++)
            q[i]=q[i].DOWN();
        if(verifica())
        {
            for(int i=0; i<4; i++)
                q[i]=q[i].UP();
            aux++;
        }
        COLOR();
        return aux;
    }
    void LEFT()
    {
        APAGA();
        for(int i=0; i<4; i++)
            q[i]=q[i].LEFT();
        if(verifica())
            for(int i=0; i<4; i++)
                q[i]=q[i].RIGHT();
        COLOR();
    }
    void RIGHT()
    {
        APAGA();
        for(int i=0; i<4; i++)
            q[i]=q[i].RIGHT();
        if(verifica())
            for(int i=0; i<4; i++)
                q[i]=q[i].LEFT();
        COLOR();
    }
    void APAGA()
    {
        for(int i=0; i<4; i++)
            if(q[i].y>=0&&q[i].y<20&&q[i].x>=0&&q[i].x<10)
                matriz[q[i].y][q[i].x]=0;
            s.APAGA();
    }
    void COLOR()
    {
		s.ATUALIZAR(q);
        for(int i=0; i<4; i++)
            if(q[i].y>=0)
                matriz[q[i].y][q[i].x]=cor;
    }
	virtual void FORMAR() {}//Define as possíveis posições das peças
    virtual void GIRAR() // Função valida para 4 posições
    {
        t=0;
        APAGA();
        if(++posicao>=n_posicao) posicao=0;
        FORMAR();
        while(1)
        {
            if(!verifica())
                break;
            for(int i=0; i<4; i++)
                q[i]=q[i].LEFT();
            if(!verifica())
                break;
            for(int i=0; i<4; i++)
                q[i]=q[i].RIGHT();
            for(int i=0; i<4; i++)
                q[i]=q[i].RIGHT();
            if(!verifica())
                break;
            for(int i=0; i<4; i++)
                q[i]=q[i].LEFT();
                for(int i=0; i<4; i++)
                q[i]=q[i].DOWN();
            if(!verifica())
                break;
            for(int i=0; i<4; i++)
                q[i]=q[i].UP();
                for(int i=0; i<4; i++)
                q[i]=q[i].UP();
            if(!verifica())
                break;
            for(int i=0; i<4; i++)
                q[i]=q[i].DOWN();
            if(--posicao<0) posicao=n_posicao-1;
                break;
        }

        FORMAR();
        COLOR();
    }
};
class T_peca: public peca
{
public:
    T_peca():peca(7)
    {
        posicao=3;
        q[0].define(4,-2);
        FORMAR();
        COLOR();
    }
    void FORMAR()
    {
        switch (posicao)
        {
        case 0:
            q[1]=q[0].DOWN();
            q[2]=q[0].UP();
            q[3]=q[0].RIGHT();
            break;
        case 1:
            q[1]=q[0].LEFT();
            q[2]=q[0].RIGHT();
            q[3]=q[0].DOWN();
            break;
        case 2:
            q[1]=q[0].LEFT();
            q[2]=q[0].UP();
            q[3]=q[0].DOWN();
            break;
        case 3:
            q[1]=q[0].LEFT();
            q[2]=q[0].UP();
            q[3]=q[0].RIGHT();
            break;
        }
    }
};
class L_peca: public peca
{
public:
    L_peca():peca(4)
    {
        posicao=0;
        q[0].define(4,-2);
        FORMAR();
        COLOR();
    }
    void FORMAR()
    {
        switch (posicao)
        {
        case 0:
            q[1]=q[0].DOWN();
            q[2]=q[0].UP();
            q[3]=q[0].RIGHT().DOWN();
            break;
        case 1:
            q[1]=q[0].LEFT();
            q[2]=q[0].RIGHT();
            q[3]=q[0].DOWN().LEFT();
            break;
        case 2:
            q[1]=q[0].LEFT().UP();
            q[2]=q[0].UP();
            q[3]=q[0].DOWN();
            break;
        case 3:
            q[1]=q[0].LEFT();
            q[2]=q[0].UP().RIGHT();
            q[3]=q[0].RIGHT();
            break;
        }
    }
};
class J_peca: public peca
{
public:
    J_peca():peca(2)
    {
        posicao=0;
        q[0].define(4,-2);
        FORMAR();
        COLOR();
    }
    void FORMAR()
    {
        switch (posicao)
        {
        case 0:
            q[1]=q[0].UP();
            q[2]=q[0].DOWN().LEFT();
            q[3]=q[0].DOWN();
            break;
        case 1:
            q[1]=q[0].LEFT();
            q[2]=q[0].RIGHT();
            q[3]=q[0].UP().LEFT();
            break;
        case 2:
            q[1]=q[0].RIGHT().UP();
            q[2]=q[0].UP();
            q[3]=q[0].DOWN();
            break;
        case 3:
            q[1]=q[0].LEFT();
            q[2]=q[0].DOWN().RIGHT();
            q[3]=q[0].RIGHT();
            break;
        }
    }
};
class Z_peca: public peca
{
public:
    Z_peca():peca(5,2)
    {
        posicao=1;
        q[0].define(4,-2);
        FORMAR();
        COLOR();
    }
    void FORMAR()
    {
        switch (posicao)
        {
        case 0:
            q[1]=q[0].RIGHT();
            q[2]=q[0].UP();
            q[3]=q[0].LEFT().UP();
            break;
        case 1:
            q[1]=q[0].RIGHT().UP();
            q[2]=q[0].RIGHT();
            q[3]=q[0].DOWN();
            break;
        }
    }
};
class S_peca: public peca
{
public:
    S_peca():peca(6,2)
    {
        posicao=1;
        q[0].define(4,-2);
        FORMAR();
        COLOR();
    }
    void FORMAR()
    {
        switch (posicao)
        {
        case 0:
            q[1]=q[0].RIGHT();
            q[2]=q[0].DOWN();
            q[3]=q[0].LEFT().DOWN();
            break;
        case 1:
            q[1]=q[0].RIGHT().DOWN();
            q[2]=q[0].RIGHT();
            q[3]=q[0].UP();
            break;
        }
    }
};
class I_peca: public peca
{
public:
    I_peca():peca(3,2)
    {
        posicao=0;
        q[0].define(4,-2);
        FORMAR();
        COLOR();
    }
    void FORMAR()
    {
        switch (posicao)
        {
        case 0:
            q[1]=q[0].UP();
            q[2]=q[0].DOWN();
            q[3]=q[0].UP().UP();
            break;
        case 1:
            q[1]=q[0].RIGHT().RIGHT();
            q[2]=q[0].RIGHT();
            q[3]=q[0].LEFT();
            break;
        }
    }
};
class O_peca: public peca
{
public:
    O_peca():peca(1,1)
    {
        posicao=0;
        q[0].define(4,-2);
        FORMAR();
        COLOR();
    }
    void FORMAR()
    {
        switch (posicao)
        {
        case 0:
            q[1]=q[0].RIGHT();
            q[2]=q[0].UP();
            q[3]=q[0].RIGHT().UP();
            break;
        }
    }
};
