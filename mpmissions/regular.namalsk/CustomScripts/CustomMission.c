Class spawn(){
void SpawnObject( string type, vector position)
{
auto obj = GetGame().CreateObject( type, position );
obj.SetPosition( position );
};

void SpawnAnimal(string anmClass , Vector pos)
{
    //vector pos = SnapToGround(Vector(5513.33,117.502,8141.14));
    //string zmbClass = "Animal_HMG_Bear_Cocaine_T0";


    EntityAI AIanm = GetGame().CreateObject( anmClass, pos, false, true );
    ref AnimalBase Bsanm;
    Class.CastTo(Bsanm,AIanm);
                        // Bszmb.AttachEventHandle(PossibleLootDrops,PossibleWeaponDrops,dropChance); for later use
    m_SpawnedZombies.Insert(AIanm);
                        //  SpawnObject(zmbClass , pos);
};
}