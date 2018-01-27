class character
{
  /*Character Class for "MyLittleIOTNode"*/
  public:

    //rebirth function
    void rebirth();
    
    //i2c data functions
    unsigned byte get_id();
    void set_id();

    //energy functions
    unsigned int get_energy();
    void set_energy();
    void add_energy();
    void takeAway_energy();

    //hunger functions;
    unsigned int get_hunger();
    void set_hunger();
    void add_hunger();
    void takeAway_hunger();

    //happiness functions;
    unsigned int get_happiness();
    void set_happiness();
    void add_happiness();
    void takeAway_happiness();

    //life functions;
    bool getLife();

    //deathCNT functions
    unsigned int get_deathCNT();
    void reset_deathCNT();
    void increaseDeathCNT();

    //faceNo functions
    unsigned int get_faceNo();
    void set_faceNo(unsigned int face);

    //cmd functions
    unsigned byte get_cmd();
    void set_cmd();
    
  private:

    char message[80];
    
    unsigned byte i2c_id; //slave id;
    unsigned byte cmd;    //i2c commmand;
    
    unsigned int energy;
    unsigned int hunger;
    unsigned int happiness;
    unsigned int deathCNT;

    unsigned int faceNo;
    
    bool life;

    void setLifeFalse();  //private data member function to kill character 
    void setLifeTrue();   //private data member functions to give life to character
};

