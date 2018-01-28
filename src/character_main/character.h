class character
{
  /*Character Class for "MyLittleIOTNode"*/
  public:

    character(unsigned char deviceID = 0x00);

    //rebirth function
    void rebirth();
    
    //i2c data functions
    unsigned char get_id();
    void set_id(unsigned char deviceID);

    //energy functions
    unsigned int get_energy();
    void set_energy(unsigned int energyValue);
    void add_energy();
    void takeAway_energy();

    //hunger functions;
    unsigned int get_hunger();
    void set_hunger(unsigned int hungriness);
    void add_hunger();
    void takeAway_hunger();

    //happiness functions;
    unsigned int get_happiness();
    void set_happiness(unsigned int happy);
    void add_happiness();
    void takeAway_happiness();

    //life functions;
    bool get_life();

    //deathCNT functions
    unsigned int get_deathCNT();
    void reset_deathCNT();
    void increaseDeathCNT();

    //faceNo functions
    unsigned int get_faceNo();
    void set_faceNo(unsigned int face);

    //cmd functions
    unsigned char get_cmd();
    void set_cmd(unsigned char command);
    
  private:

    char message[80];
    
    unsigned char i2c_id; //slave id;
    unsigned char cmd;    //i2c commmand;
    
    unsigned int energy;
    unsigned int hunger;
    unsigned int happiness;
    unsigned int deathCNT;

    unsigned int faceNo;
    
    bool life;

    void setLifeFalse();  //private data member function to kill character 
    void setLifeTrue();   //private data member functions to give life to character
};

