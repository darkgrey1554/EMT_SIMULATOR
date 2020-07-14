#include "LibGate_EMT_DTS.h"

std::ostream& operator<<(std::ostream& out, TypeSignal& m)
{
    if (m == TypeSignal::INPUT) out << "InPut";
    if (m == TypeSignal::OUTPUT) out << "OutPut";
    if (m == TypeSignal::EMPTY) out << "Empty";
    return out;
}

std::ostream& operator<<(std::ostream& out, TypeData& m)
{
    if (m == TypeData::ANALOG) out << "Analog";
    if (m == TypeData::DISCRETE) out << "Discrete";
    if (m == TypeData::BINAR) out << "Binar";
    if (m == TypeData::GROUP) out << "Group";
    if (m == TypeData::EMPTY) out << "Empty";
    return out;
}

int Gate_EMT_DTS::ReadConfigFile(const char* filename)
{

    FILE* config_file = NULL;
    char simvol = 0;
    std::string str_info;
    std::string helpstr;
    int res_read = 0;
    int pos[2] = { 0,0 };
    InfoSharedMemory unit;
    int count = 0;

    config_file = fopen(filename, "r");
    if (config_file == NULL)
    {
        std::cout << "MAIN\tERROR_OPEN_CONFIG_FILE" << std::endl;
        return -1;
    }

    for (;;)
    {
        simvol = 0;
        str_info.clear();
        while (simvol != '\n' && res_read != EOF)
        {
            res_read = fscanf(config_file, "%c", &simvol);
            if ((simvol > 0x1F || simvol == '\t') && res_read != EOF) str_info += simvol;
        }

        if (str_info == "[List]" || res_read == EOF)
        {
            if (res_read == EOF)
            {
                std::cout << "MAIN\tERROR_FORMATION_OF_CONFIG_FILE1" << std::endl;
                return -1;
            }
            break;
        }

        if (str_info.substr(0, 4) == "@EMT")
        {
            pos[0] = 0;
            pos[1] = 0;
            unit.clear();

            if (str_info.find("Input") != -1)
            {
                unit.type_signal = TypeSignal::INPUT;
            }
            else if (str_info.find("Output") != -1)
            {
                unit.type_signal = TypeSignal::OUTPUT;
            }
            else
            {
                std::cout << "MAIN\tERROR_FORMATION_OF_CONFIG_FILE2" << std::endl;
                return -1;
            }

            if (str_info.find("Discrete") != -1)
            {
                unit.type_data = TypeData::DISCRETE;
            }
            else if (str_info.find("Analog") != -1)
            {
                unit.type_data = TypeData::ANALOG;
            }
            else if (str_info.find("Binar") != -1)
            {
                unit.type_data = TypeData::BINAR;
            }
            else if (str_info.find("Group") != -1)
            {
                unit.type_data = TypeData::GROUP;
            }
            else
            {
                std::cout << "MAIN\tERROR_FORMATION_OF_CONFIG_FILE3" << std::endl;
                return -1;
            }

            pos[0] = str_info.find('\t', 0);
            if (pos[0] == -1)
            {
                std::cout << "MAIN\tERROR_FORMATION_OF_CONFIG_FILE4" << std::endl;
                return -1;
            }

            pos[1] = str_info.find('\t', (size_t)pos[0] + 1);
            if (pos[1] == -1)
            {
                std::cout << "MAIN\tERROR_FORMATION_OF_CONFIG_FILE5" << std::endl;
                return -1;
            }
            helpstr.clear();
            helpstr = str_info.substr((size_t)pos[0] + 1, (size_t)pos[1] - pos[0] - 1);
            unit.size_data = atoi(helpstr.c_str());

            pos[0] = pos[1];
            pos[1] = str_info.find('\t', (size_t)pos[0] + 1);
            if (pos[1] == -1)
            {
                std::cout << "MAIN\tERROR_FORMATION_OF_CONFIG_FILE6" << std::endl;
                return -1;
            }
            helpstr.clear();
            helpstr = str_info.substr((size_t)pos[0] + 1, (size_t)pos[1] - pos[0] - 1);
            unit.namememory = helpstr;

            pos[0] = pos[1];
            pos[1] = str_info.find('\t', (size_t)pos[0] + 1);
            if (pos[1] == -1)
            {
                std::cout << "MAIN\tERROR_FORMATION_OF_CONFIG_FILE7" << std::endl;
                return -1;
            }
            //helpstr.clear();
            //helpstr = str_info.substr((size_t)pos[0] + 1, (size_t)pos[1] - pos[0] - 1);
            //unit.ip_address = helpstr;

            pos[0] = pos[1];
            pos[1] = str_info.find('\t', (size_t)pos[0] + 1);
            if (pos[1] == -1)
            {
                std::cout << "MAIN\tERROR_FORMATION_OF_CONFIG_FILE8" << std::endl;
                return -1;
            }
            //helpstr.clear();
            //helpstr = str_info.substr((size_t)pos[0] + 1, (size_t)pos[1] - pos[0] - 1);
            //unit.port = atoi(helpstr.c_str());

            pos[0] = pos[1];
            pos[1] = str_info.find('\t', (size_t)pos[0] + 1);
            if (pos[1] == -1)
            {
                std::cout << "MAIN\tERROR_FORMATION_OF_CONFIG_FILE9" << std::endl;
                return -1;
            }
            //helpstr.clear();
            //helpstr = str_info.substr((size_t)pos[0] + 1, (size_t)pos[1] - pos[0] - 1);
            //unit.frequency_time = atoi(helpstr.c_str());

            //unit.id_unit = count;
            count++;
            infovector.push_back(unit);

        }
        else if (str_info.substr(0, 5) != "[EMT]")
        {
            std::cout << "MAIN\tERROR_FORMATION_OF_CONFIG_FILE10" << std::endl;
            return -1;
        }
    }
    fclose(config_file);
    return 0;
}


int Gate_EMT_DTS::Init(const char* filename)
{
    if (ReadConfigFile(filename) == -1) return -1;

    for (int i = 0; i < infovector.size(); i++)
    {

        if (infovector[i].type_data == TypeData::ANALOG || infovector[i].type_data == TypeData::DISCRETE) infovector[i].k = 4;
        if (infovector[i].type_data == TypeData::BINAR || infovector[i].type_data == TypeData::GROUP) infovector[i].k = 1;

        int size_data_byte=0;

        if (infovector[i].type_data != TypeData::GROUP)
        {
            size_data_byte = infovector[i].size_data * infovector[i].k;
        }
        else
        {
            size_data_byte = 4108;
        }

        std::string mutexname = "mutex";
        mutexname += infovector[i].namememory.c_str();

        std::string semaphorname = "semaphor";
        semaphorname += infovector[i].namememory.c_str();

        infovector[i].mutex = CreateMutexA(NULL, FALSE, mutexname.c_str());
        if (infovector[i].mutex == NULL)
        {
            std::cout << "\tERROR_INITIALIZATION_MUTEX\tCODE_ERROR: " << GetLastError() << std::endl;
            return -1;
        }

        infovector[i].semaphor = CreateSemaphoreA(NULL, 0, 1, semaphorname.c_str());
        if (infovector[i].semaphor == NULL)
        {
            std::cout << "\tERROR_INITIALIZATION_SEMAPHOR\tCODE_ERROR: " << GetLastError() << std::endl;
            return -1;
        }

        infovector[i].memory = CreateFileMappingA(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, size_data_byte, infovector[i].namememory.c_str());
        if (infovector[i].memory == NULL)
        {
            std::cout  << "\tERROR_INITIALIZATION_SHARED_MEMORY\tCODE_ERROR: " << GetLastError() << std::endl;
            return -1;
        }
        infovector[i].buffer = MapViewOfFile(infovector[i].memory, FILE_MAP_ALL_ACCESS, 0, 0, size_data_byte);
        if (infovector[i].buffer == NULL)
        {
            std::cout << "\tERROR_INITIALIZATION_MAPVIEW\tCODE_ERROR: " << GetLastError() << std::endl;
            return -1;
        }
    }

    return 0;
}

int Gate_EMT_DTS::WriteData(void* buf, TypeData td, int size, int index, int grtype)
{
    int res;
    char* ibuf = (char*)buf;
    char* jbuf;
    int sizedata = 0;
    HANDLE mut;
    HANDLE sem;
    for (int i = 0; i < infovector.size(); i++)
    {
        if (infovector[i].type_data == td && infovector[i].type_signal == TypeSignal::OUTPUT)
        {
            mut = infovector[i].mutex;
            sem = infovector[i].semaphor;
            sizedata = infovector[i].size_data*infovector[i].k;
            jbuf = (char*)infovector[i].buffer;
            if (td == TypeData::GROUP)
            {
                if (size > 4096)
                {
                    std::cout << "GATE_EMT_DTS\tERROR_WRITEDATA: BAD SIZE" << std::endl;
                    return -1;
                }
            }

            res=WaitForSingleObject(mut, INFINITE);
            if (td == TypeData::GROUP)
            {
                for (int i = 0; i < 4; i++)
                {
                    *(jbuf + i) = *(((char*)&index) + i);
                    *(jbuf + 4 + i) = *(((char*)&grtype) + i);
                    *(jbuf + 8 + i) = *(((char*)&size) + i);
                }
                jbuf += 12;
                sizedata = size;
            }

            for (int i = 0; i < sizedata; i++)
            {
                *jbuf = *ibuf;
                jbuf++;
                ibuf++;
            }
            res=ReleaseMutex(mut);
            res=ReleaseSemaphore(sem, 1, NULL);
            
            return 0;
        }
        else continue;

        return 0;
    }
    std::cout << "GATE_EMT_DTS\tERROR_WRITEDATA: UNIT NOT FOUND" << std::endl;
    return -1;
}

int Gate_EMT_DTS::ReadData(void* buf, TypeData td, int* size, int* index, int* grtype)
{
    char* ibuf = (char*)buf;
    char* jbuf;
    int sizedata = 0;

    for (int i = 0; i < infovector.size(); i++)
    {
        if (infovector[i].type_data == td && infovector[i].type_signal==TypeSignal::INPUT)
        {
            jbuf = (char*)infovector[i].buffer;
            sizedata = infovector[i].size_data * infovector[i].k;
 
            WaitForSingleObject(infovector[i].mutex, INFINITE);

            if (td == TypeData::GROUP)
            {
                *index = *(int*)(jbuf);
                *grtype = *(int*)(jbuf+4);
                *size=*(int*)(jbuf+8);
                jbuf += 12;
                sizedata = 4096;
            }

            for (int i = 0; i < sizedata; i++)
            {
                *ibuf = *jbuf;
                jbuf++;
                ibuf++;
            }
            ReleaseMutex(infovector[i].mutex);
            return 0;
        }
        else continue;
        return 0;
    }
    std::cout << "GATE_EMT_DTS\tERROR_READDATA: UNIT NOT FOUND" << std::endl;
    return -1;
}

int Gate_EMT_DTS::ReadAnalogData(void* buf)
{
    return ReadData(buf, TypeData::ANALOG);
}

int Gate_EMT_DTS::ReadDiscreteData(void* buf)
{
    return ReadData(buf, TypeData::DISCRETE);
}

int Gate_EMT_DTS::ReadBinarData(void* buf)
{
    return ReadData(buf, TypeData::BINAR);
}

int Gate_EMT_DTS::ReadGroupData(void* buf, int* size, int* index, int* grtype)
{
    return ReadData(buf, TypeData::GROUP ,size, index, grtype);
}

int Gate_EMT_DTS::WriteAnalogData(void* buf)
{
    return WriteData(buf, TypeData::ANALOG);
}

int Gate_EMT_DTS::WriteDiscreteData(void* buf)
{
    return WriteData(buf, TypeData::DISCRETE);
}

int Gate_EMT_DTS::WriteBinarData(void* buf)
{
    return WriteData(buf, TypeData::BINAR);
}

int Gate_EMT_DTS::WriteGroupData(void* buf, int size, int index, int grtype)
{
    return WriteData(buf, TypeData::GROUP, size, index, grtype);
}

Gate_EMT_DTS::Gate_EMT_DTS() {};
Gate_EMT_DTS::~Gate_EMT_DTS() {};