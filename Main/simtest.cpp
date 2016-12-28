#include <Interface/SimTestGUI.h>
#include <stdio.h>
int main(int argc,const char** argv)
{
  RobotWorld world;
  SimTestBackend backend(&world);
  if(!backend.LoadAndInitSim(argc,argv)) {
    return 1;
  }
  GLUISimTestGUI gui(&backend,&world);
  gui.SetWindowTitle("SimTest3.0");
  gui.Run();
  return 0;
}
