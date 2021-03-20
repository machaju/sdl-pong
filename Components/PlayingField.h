class PlayingField
{
public:
    PlayingField(int width, int height);
    ~PlayingField(); 

    // size of the playing field
    int height  { 0 };
    int width   { 0 };

    // the position of the playing field       
    int x       { 0 };
    int y       { 0 };   
};