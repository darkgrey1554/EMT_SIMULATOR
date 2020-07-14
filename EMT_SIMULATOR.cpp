// EMT_SIMULATOR.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include "LibGate_EMT_DTS.h"

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
    std::cout << (int)*fin <<" - "<< (int)*(fin+99) <<std::endl;
    goto next;

    

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
}

