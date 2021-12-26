
void initPreferences(){
pref.begin("parametres",false);
}

void chargerCalibration(){
        zx=pref.getInt("ZeroX", 0);
        zy=pref.getInt("ZeroY", 0);
        zz=pref.getInt("ZeroZ", 0);
        mabsx=pref.getInt("MaxX", 0);
        mabsy=pref.getInt("MaxY", 0);
        mabsz=pref.getInt("MaxZ", 0);  
}
