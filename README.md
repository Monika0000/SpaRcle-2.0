# SpaRcle-2.0

(Lua scripting)
All base functions : 
   * function Start  () -- call at starup engine
   * function Update () -- call every tick (120 tick / sek)
All global variables : 
   * Time (float)
All classes :
   * GameObject
      - void Move(float x, float y, float z)
      - void Rotate(float x, float y, float z)
   * World
      - static GameObject* Find(std::string name)
   * Debug
      - Log(std::string msg)
      - Log(int msg)
      - Log(double msg)
      - Error(std::string msg)
