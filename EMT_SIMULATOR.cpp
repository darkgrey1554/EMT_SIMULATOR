// EMT_SIMULATOR.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "LibGate_EMT_DTS.h"

#define SIZE 100

int main()
{

    Gate_EMT_DTS* gate = new Gate_EMT_DTS();
    int res = gate->Init("conf.txt");

    /// --- Binar Data --- ///
    /*
    char* fout = new char[100];
    char* fin = new char[100];
    int tick = 0;
next:

    for (int i = 0; i < 100; i++)
    {
        fout[i] = (tick + i)%2;
        if (fout[i] < 0) fout[i] *= -1;
    }
    tick++;
    res=gate->WriteBinarData(fout);
    Sleep(1000);
    gate->ReadBinarData(fin);
    std::cout << (int)*fin <<" - "<< (int)*(fin+99) <<std::endl;
    goto next;
    */
    /// --- Discrete Data --- ///
    /*
    int* fout = new int[100];
    int* fin = new int[100];
    int tick = 0;
next:

    for (int i = 0; i < 100; i++)
    {
        fout[i] = (tick + i);
    }
    tick++;
    res=gate->WriteDiscreteData(fout);
    Sleep(1000);
    gate->ReadDiscreteData(fin);
    std::cout << (int)*fin <<" - "<< (int)*(fin+99) <<std::endl;
    goto next;
    */

    /// --- Analog Data --- ///
    /*
    float* fout = new float[100];
    float* fin = new float[100];
    int tick = 0;

    next:

    for (int i = 0; i < 100; i++)
    {
        fout[i] = (tick + i)+0.1;
    }
    tick++;
    res=gate->WriteAnalogData(fout);
    Sleep(1000);
    gate->ReadAnalogData(fin);
    std::cout << *fin <<" - "<< *(fin+99) <<std::endl;
    goto next;
    */
    

    /// --- Group Data --- ///
   /*
    char* fout = new char[4108];
    char* fin = new char[4108];
    int tick = 0;
    int indexout = 1;
    int grouptypeout = 1;
    int sizeout = 22;
    int indexin = 0;
    int grouptypein = 0;
    int sizein = 0;
next:

    for (int i = 0; i < sizeout; i++)
    {
        *(fout + i) = (tick + i);
    }
    tick++;
    res=gate->WriteGroupData(fout,sizeout,indexout, grouptypeout);
    
    gate->ReadGroupData(fin, &sizein, &indexin, &grouptypein);
    
    std::cout << "Group Data:" << std::endl;
    std::cout << "index - "<< indexin << std::endl;
    std::cout << "grouptype - " << grouptypein << std::endl;
    std::cout << "size - " << sizein << std::endl;
    std::cout << "data - ";
    for (int i = 0; i < sizein; i++)
    {
        std::cout << (int)*(fin + i)<<"|";
    }
    std::cout << std::endl;
    std::cout << std::endl;
    Sleep(3000);
    goto next;
   */
    
    /*char* bout = new char[100];
    char* bin = new char[100];

    int* dout = new int[100];
    int* din = new int[100];

    float* fout = new float[100];
    float* fin = new float[100];

    char* gout = new char[4096];
    char* gin = new char[4096];
    int indexout = 1;
    int grouptypeout = 1;
    int sizeout = 22;
    int indexin = 0;
    int grouptypein = 0;
    int sizein = 0;

    int tick = 0;
next:

    for (int i = 0; i < 100; i++)
    {
        bout[i] = (tick + i) % 2;
        if (bout[i] < 0) bout[i] *= -1;
    }
    res = gate->WriteBinarData(bout, SIZE);

    for (int i = 0; i < 100; i++)
    {
        dout[i] = (tick + i);
    }
    res = gate->WriteDiscreteData(dout , SIZE*4);

    for (int i = 0; i < 100; i++)
    {
        fout[i] = (tick + i) + 0.1;
    }
    res = gate->WriteAnalogData(fout, SIZE*4);

    for (int i = 0; i < sizeout; i++)
    {
        *(gout + i) = (tick + i);
    }
    res = gate->WriteGroupData(gout, 4096, sizeout, indexout, grouptypeout);

    tick++;


    gate->ReadBinarData(bin, SIZE);
    std::cout << "BINAR:"<<std::endl;
    std::cout << (int)*bin << " - " << (int)*(bin + 99) << std::endl;
    std::cout << std::endl;
    
    gate->ReadDiscreteData(din, SIZE*4);
    std::cout << "DISCRETE:" << std::endl;
    std::cout << (int)*din << " - " << (int)*(din + 99) << std::endl;
    std::cout << std::endl;

    gate->ReadAnalogData(fin, SIZE*4);
    std::cout << "ANALOG:" << std::endl;
    std::cout << *fin << " - " << *(fin + 99) << std::endl;
    std::cout << std::endl;

    gate->ReadGroupData(gin, 4096,&sizein, &indexin, &grouptypein);

    std::cout << "Group Data:" << std::endl;
    std::cout << "index - " << indexin << std::endl;
    std::cout << "grouptype - " << grouptypein << std::endl;
    std::cout << "size - " << sizein << std::endl;
    std::cout << "data - ";
    for (int i = 0; i < sizein; i++)
    {
        std::cout << (int)*(gin + i) << "|";
    }
    std::cout << std::endl;
    std::cout << "-------------------------------------"<< std::endl;
    std::cout << std::endl;

    Sleep(1000);
    goto next; */

    ///////////////////////////////////////////////////////////////////////////////////////////
    char* bout =0; int sizebout;
    char* bin =0; int sizebin;
    int* dout =0; int sizedout;
    int* din =0; int sizedin;
    float* fout =0; int sizefout;
    float* fin =0; int sizefin;
    char* gout =0; int sizegout;
    char* gin =0; int sizegin;

    int indexout = 1;
    int grouptypeout = 1;
    int sizeout = 22;
    int indexin = 0;
    int grouptypein = 0;
    int sizein = 0;

    int tick = 0;
    
    sizebout = gate->ReadSizeData(TypeSignal::OUTPUT, TypeData::BINAR);
    sizebin = gate->ReadSizeData(TypeSignal::INPUT, TypeData::BINAR);
    sizedout = gate->ReadSizeData(TypeSignal::OUTPUT, TypeData::DISCRETE);
    sizedin = gate->ReadSizeData(TypeSignal::INPUT, TypeData::DISCRETE);
    sizefout = gate->ReadSizeData(TypeSignal::OUTPUT, TypeData::ANALOG);
    sizefin = gate->ReadSizeData(TypeSignal::INPUT, TypeData::ANALOG);
    sizegout = gate->ReadSizeData(TypeSignal::OUTPUT, TypeData::GROUP);
    sizegin = gate->ReadSizeData(TypeSignal::INPUT, TypeData::GROUP);

    if (sizebout != -1) bout = new char[sizebout];
    if (sizebin != -1) bin = new char[sizebin];
    if (sizedout != -1) dout = new int[sizedout];
    if (sizedin != -1) din = new int[sizedin];
    if (sizefout != -1) fout = new float[sizefout];
    if (sizefin!= -1) fin = new float[sizefin];
    if (sizegout != -1) gout = new char[4096];
    if (sizegin != -1) gin = new char[4096];

    next:

    if (sizebout != -1)
    {
        for (int i = 0; i < sizebout; i++)
        {
            bout[i] = (tick + i) % 2;
            if (bout[i] < 0) bout[i] *= -1;
        }
        res = gate->WriteBinarData(bout, sizebout);
        if (res == 0) { std::cout << "WriteBinarData : DONE" << std::endl; }
        else { std::cout << "WriteBinarData : FALSE" << std::endl; };
    }
    
    if (sizedout != -1)
    {
        for (int i = 0; i < sizedout; i++)
        {
            dout[i] = (tick + i);
        }
        res = gate->WriteDiscreteData(dout, sizedout*4);
        if (res == 0) { std::cout << ">WriteDiscreteData : DONE" << std::endl; }
        else { std::cout << "WriteDiscreteData : FALSE" << std::endl; };
    }

    if (sizefout != -1)
    {
        for (int i = 0; i < sizefout; i++)
        {
            fout[i] = (tick + i) + 0.1;
        }
        res = gate->WriteAnalogData(fout, sizefout*4);
        if (res == 0) { std::cout << "WriteAnalogData : DONE" << std::endl; }
        else { std::cout << "WriteAnalogData : FALSE" << std::endl; };
    }

    
    if (sizegout != -1)
    {
        for (int i = 0; i < sizeout; i++)
        {
            *(gout + i) = (tick + i);
        }
        res = gate->WriteGroupData(gout, 4096, sizeout, indexout, grouptypeout);
        if (res == 0) { std::cout << "WriteGroupData : DONE" << std::endl; }
        else { std::cout << "WriteGroupData : FALSE" << std::endl; };
    }
    tick++;

    if (sizebin != -1)
    {
        gate->ReadBinarData(bin, sizebin);
        std::cout << "BINAR:" << std::endl;
        std::cout << (int)*bin << " - " << (int)*(bin + sizebin-1) << std::endl;
        std::cout << std::endl;
    }

    if (sizedin != -1)
    {
        gate->ReadDiscreteData(din, sizedin * 4);
        std::cout << "DISCRETE:" << std::endl;
        std::cout << (int)*din << " - " << (int)*(din + sizedin -1) << std::endl;
        std::cout << std::endl;
    }

    if (sizefin != -1)
    {
        gate->ReadAnalogData(fin, sizefin * 4);
        std::cout << "ANALOG:" << std::endl;
        std::cout << *fin << " - " << *(fin + sizefin -1) << std::endl;
        std::cout << std::endl;
    }

    if (sizegin != -1)
    {
        gate->ReadGroupData(gin, 4096, &sizein, &indexin, &grouptypein);

        std::cout << "Group Data:" << std::endl;
        std::cout << "index - " << indexin << std::endl;
        std::cout << "grouptype - " << grouptypein << std::endl;
        std::cout << "size - " << sizein << std::endl;
        std::cout << "data - ";
        for (int i = 0; i < sizein; i++)
        {
            std::cout << (int)*(gin + i) << "|";
        }
        std::cout << std::endl;
        
    }
    std::cout << "-------------------------------------" << std::endl;
    std::cout << std::endl;

    Sleep(1000);

    goto next;
    

}

