#include <iostream>
#include <vector>
using namespace std;

class PS_Base;

class PS_Machine {
    PS_Base* current_state;
    
    vector<PS_Base*> states;
    
public:
    PS_Machine() {
        // push_back all states
        states.push_back(new PS_Walking(this));
        states.push_back(new PS_Offend(this));
        states.push_back(new PS_Defend(this));
    }
    
    ~PS_Machine() {
        for(int i = 0; i < states.size(); i++) {
            delete states[i];
            states[i] = nullptr;
        }
    }
    
    void changeState(int nextState) {
        current_state = states[nextState];
    }
};

class PS_Base {    
protected:
    string state_name;
    
    PS_Machine* machine;
    PS_Base(PS_Machine* parent): machine(parent) {
        
    }
    
    virtual void onKeyPressed() = 0;
    
public:
    virtual ~PS_Base() {
        
    }
};

class PS_Walking: public virtual PS_Base{
public:
    PS_Walking(PS_Machine* machine): PS_Base(machine) {
        state_name = "Walking";
    }
    
    void onKeyPressed() {
        // 假设存在一个提供当前按下的键盘按键的函数：getPressedKeys(), 返回值类型为vector<KeyCode>，其中KeyCode为枚举类型(int)
        auto pressed_keys = getPressedKeys();
        for(auto& key : pressed_keys) {
            switch(key) {
                case KeyCode.A: break;
                    parent->changeState(1);
                case KeyCode.B: break;
                    parent->changeState(2);
            }
        }
    }
    
    ~PS_Walking() {
        
    }
};

class PS_Offend: public virtual PS_Base {
public:
    PS_Offend(PS_Machine* machine) : PS_Base(machine) {
        state_name = "Offend";
    }
    
    void onKeyPressed() {
        // 假设存在一个提供当前按下的键盘按键的函数：getPressedKeys(), 返回值类型为vector<KeyCode>，其中KeyCode为枚举类型
        auto pressed_keys = getPressedKeys();
        for(auto& key : pressed_keys) {
            switch(key) {
                case KeyCode.A: break;
                    parent->changeState(0);
                case KeyCode.B: break;
                    parent->changeState(2);
            }
        }
    }
    
    ~PS_Offend() {}
};

class PS_Defend: public virtual PS_Base {
public:
    PS_Defend(PS_Machine* machine) : PS_Base(machine) {
        state_name = "Defend";
    }
    
    void onKeyPressed() {
        // 假设存在一个提供当前按下的键盘按键的函数：getPressedKeys(), 返回值类型为vector<KeyCode>，其中KeyCode为枚举类型
        auto pressed_keys = getPressedKeys();
        for(auto& key : pressed_keys) {
            switch(key) {
                case KeyCode.A: break;
                    parent->changeState(1);
                    
                case KeyCode.B: break;
                    parent->changeState(2);
                    
            }
        }
    }
};
