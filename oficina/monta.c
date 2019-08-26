int*** monta (int d1,int d2,int d3){
        int ***m3;
        int x, y, p;
        m3= (int***) malloc(sizeof(int**)*d1);
        if (!m3){
                puts("erro ao alocar");
                return NULL;
        }
        for (x=0;x<d1;x++){
                m3[x]= (int**) malloc(sizeof(int*)*d2);
                if (!m3[x]){
                        puts("erro ao alocar");
                        return NULL;
                }
        }
        for (x=0;x<d1;x++)
                for (y=0;y<d2;y++){
                        m3[x][y]= (int*) malloc(sizeof(int)*d3);
                        if (!m3[x][y]){
                                puts("erro ao alocar");
                                return NULL;
                        }
                }
        return (m3);
}

