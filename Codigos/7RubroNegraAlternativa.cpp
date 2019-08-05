    while((umNoh != mRaiz) and (umNoh->mPai->mCor = VERMELHO)){
        Noh* Tio = NULL;
        if(umNoh->mPai == mRaiz){
            Tio = NULL;
        }else if(umNoh->mPai == umNoh->mPai->mPai->mEsq){
            Tio = umNoh->mPai->mPai->mDir;
        }else{
            Tio = umNoh->mPai->mPai->mEsq;
        }
        if(Tio->mCor == VERMELHO){
            Tio->mCor = PRETO;
            umNoh->mPai->mCor = PRETO;
            umNoh->mPai->mPai->mCor = VERMELHO;
            umNoh = umNoh->mPai->mPai;
        }else{
            if((umNoh->mPai == umNoh->mPai->mPai->mEsq) and (umNoh = umNoh->mPai->mEsq)){
                umNoh->mPai->mCor = PRETO;
                umNoh->mPai->mPai->mCor = VERMELHO;
                RotacionarDireita(umNoh->mPai->mPai);
            }else if((umNoh->mPai == umNoh->mPai->mPai->mDir) and (umNoh = umNoh->mPai->mDir)){
                umNoh->mPai->mCor = PRETO;
                umNoh->mPai->mPai->mCor = VERMELHO;
                RotacionarEsquerda(umNoh->mPai->mPai);
            }else if((umNoh->mPai == umNoh->mPai->mPai->mEsq) and (umNoh == umNoh->mPai->mEsq)){
                umNoh->mCor = PRETO;
                Noh* Avo = umNoh->mPai->mPai;
                Avo->mCor = VERMELHO;
                RotacionarEsquerda(umNoh->mPai);
                RotacionarDireita(Avo);
                umNoh = umNoh->mPai;
            }else{
                umNoh->mCor = PRETO;
                Noh* Avo = umNoh->mPai->mPai;
                Avo->mCor = VERMELHO;
                RotacionarDireita(umNoh->mPai);
                RotacionarEsquerda(Avo);
                umNoh = umNoh->mPai;
            }
        }
    }
    mRaiz->mCor = PRETO;
