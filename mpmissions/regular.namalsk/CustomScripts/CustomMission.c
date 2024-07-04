void expansion_onqueststart(){
override void Expansion_OnQuestStart(ExpansionQuest quest){
        ref array<EntityAI> m_SpawnedZombies = new array<EntityAI>;
        ExpansionQuestConfig questConfig = quest.GetQuestConfig();
        switch(questConfig.GetID()){
                case 1011:
                {
                        vector pos = SnapToGround(Vector(5513.33,117.502,8141.14));
                        string zmbClass = "Animal_HMG_Bear_Cocaine_T0";
                        EntityAI AIzmb = GetGame().CreateObject( zmbClass, pos, false, true );
                        ref AnimalBase Bszmb;
                        Class.CastTo(Bszmb,AIzmb);
                        // Bszmb.AttachEventHandle(PossibleLootDrops,PossibleWeaponDrops,dropChance); for later use
                         m_SpawnedZombies.Insert(AIzmb);
                        //  SpawnObject(zmbClass , pos);
                }
        break;
    }
}


void SpawnObject( string type, vector position)
{
auto obj = GetGame().CreateObject( type, position );
obj.SetPosition( position );
};

};