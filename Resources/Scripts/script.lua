--local sr = require "mymodule"
--module("mymodule", package.seeall)
    --Debug.Log("hello")
    --Debug.Error("Fail")

function Start ()
    --sphere  = World.Find("Sphere")
    --sphere2 = World.Find("Sphere (Copy)")
    sphere   = Engine.LoadPrefab("Sphere")
    sphere:SetPosition(10,0,0)
    
    sphere2  = Engine.LoadPrefab("Sphere")
    sphere2:SetPosition(14, 0,0)
    
    sina     = Engine.LoadPrefab("Sina") 
    sina:SetScale(0.3, 0.3, 0.3)
end;

function Update ()
    --Debug.Log(math.sin(Time))
    --print(math.sin(math.floor(Time)))

    local v = math.cos(Time * 10.0) / 50.0
    sphere:Move(0,0,v)
    
    sina:Rotate(0,0.05,0)
    sphere2:Rotate(0.03,0.03,0.03)
end;

