#include "qrobottestguibase.h"

QRobotTestGUIBase::QRobotTestGUIBase(GenericBackendBase *_backend, RobotWorld *_world) :
    QtGUIBase(_backend,_world),
    col_out(new CollisionOutput)

{
  const char* rules = "[ \
[{type:key_down,key:c}, {type:command,cmd:constrain_current_link,args:\"\"}],	\
[{type:key_down,key:d}, {type:command,cmd:delete_current_constraint,args:\"\"}], \
[{type:key_down,key:p}, {type:command,cmd:print_config,args:\"\"}],	\
[{type:button_press,button:print_config}, {type:command,cmd:print_pose,args:_0}], \
[{type:widget_value,widget:link,value:_0}, {type:command,cmd:set_link,args:_0}], \
[{type:widget_value,widget:link_value,value:_0}, {type:command,cmd:set_link_value,args:_0}], \
[{type:widget_value,widget:driver,value:_0}, {type:command,cmd:set_driver,args:_0}], \
[{type:widget_value,widget:driver_value,value:_0}, {type:command,cmd:set_driver_value,args:_0}] \
]";
  stringstream ss(rules);
  bool res=LoadRules(ss);
  assert(res==true);
  driver_index=0;
  link_index=0;
}

void QRobotTestGUIBase::SetDriver(int index){
    driver_index=index;
    SendCommand("set_driver",index);
    emit UpdateDriverValue();
    emit UpdateDriverParameters();
}

void QRobotTestGUIBase::SetDriverValue(double val){
    SendCommand("set_driver",driver_index);
    SendCommand("set_driver_value",val);
}

void QRobotTestGUIBase::SetLink(int index){
    link_index=index;
    SendCommand("set_link",index);
    emit UpdateLinkValue();
    emit UpdateLinkParameters();
}

void QRobotTestGUIBase::SetLinkValue(double val){
    SendCommand("set_link",link_index);
    SendCommand("set_link_value",val);
}

bool QRobotTestGUIBase::OnCommand(const string &cmd, const string &args){
    if(cmd=="update_config"){
        UpdateGUI();
        return true;
    }
    else if(cmd=="return_self_collisions"){
        string str=&(args[0]);
        col_out->SetText(QString::fromStdString(str));
        col_out->show();
    }
    else return QtGUIBase::OnCommand(cmd,args);
}

void QRobotTestGUIBase::UpdateGUI(){

    emit UpdateLinkValue();
    emit UpdateLinkParameters();
    emit UpdateDriverValue();
    emit UpdateDriverParameters();
}

void QRobotTestGUIBase::LoadFile(QString filename){
    if(filename.isEmpty()){
      QFileDialog f;
      filename = f.getOpenFileName(0,"Open File",QDir::home().absolutePath(),"");
    }
    if(!filename.isNull())
      SendCommand("load_file",filename.toStdString());
  }