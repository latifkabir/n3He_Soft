
class ReadBinary
{
public:
    FILE *ptr_myfile;
    int GetValue(int channel,long point);
    ReadBinary(const char* filename);
    ~ReadBinary();
};
