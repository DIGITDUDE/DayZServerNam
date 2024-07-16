void main()
{
	/*
	  [Namalsk] CE init (offline)
	*/
	CreateHive();
	GetHive().InitOffline();

	/*
	  [Namalsk] Mission time init
	   after CE init to determine if storage mission type is outside of the required time-frame
	   currently recommended time-frame is:
		11/1 -> 11/30
		keep in mind that gameplay features are tied to the mission date (stored in the storage) and that it SHOULD remain this period!
	   while using:
		day accelerated 6 times (serverTimeAcceleration=6), resulting in an average 78 min of day-time (RL)
		night accelerated 24 times (serverNightTimeAcceleration=4), resulting in an average of 26 min of night-time (RL)
	*/
	int year, month, day, hour, minute;
	GetGame().GetWorld().GetDate( year, month, day, hour, minute );

    if ( ( month < 11 ) || ( month >= 12 ) )
    {
    	year = 2011;
        month = 11;
        day = 1;
		
		GetGame().GetWorld().SetDate( year, month, day, hour, minute );
	}
	
};

class CustomMission: MissionServer
{
	
	override void OnInit()
	{
		super.OnInit();

		// this piece of code is recommended otherwise event system is switched on automatically and runs from default values
		// comment this whole block if NOT using Namalsk Survival
		if ( m_EventManagerServer )
		{
			// enable/disable event system, min time between events, max time between events, max number of events at the same time
			m_EventManagerServer.OnInitServer( true, 550, 1000, 2 );
			// registering events and their probability
			m_EventManagerServer.RegisterEvent( Aurora, 0.85 );
			m_EventManagerServer.RegisterEvent( Blizzard, 0.4 );
			m_EventManagerServer.RegisterEvent( ExtremeCold, 0.4 );
			m_EventManagerServer.RegisterEvent( Snowfall, 0.6 );
			m_EventManagerServer.RegisterEvent( EVRStorm, 0.35 );
			m_EventManagerServer.RegisterEvent( HeavyFog, 0.3 );
		}
	}

	void SetRandomHealth(EntityAI itemEnt)
	{
		if (itemEnt)
		{
			float rndHlt = Math.RandomFloat( 0.50, 0.85 );
			itemEnt.SetHealth01( "", "", rndHlt );
		}
	}
	void SetFullHealth(EntityAI itemEnt)
	{
		if (itemEnt)
		{
			
			itemEnt.SetHealth01( "", "", 1 );
		}
	}


	override void StartingEquipSetup( PlayerBase player, bool clothesChosen )
	{
		EntityAI itemClothing;
		EntityAI itemEnt;
		ItemBase itemBs;
		float rand;
		
		// top
		itemClothing = player.FindAttachmentBySlotName( "Body" );
		if ( itemClothing )
		{
			SetRandomHealth( itemClothing );

			itemEnt = itemClothing.GetInventory().CreateInInventory( "Rag" );
			if ( Class.CastTo( itemBs, itemEnt ) )
			{
				SetRandomHealth( itemEnt );
				itemBs.SetQuantity( 4 );
				itemBs.SetCleanness( 1 );
			}
			player.SetQuickBarEntityShortcut( itemEnt, 0 );
			
			itemEnt = itemClothing.GetInventory().CreateInInventory( "RoadFlare" );
			SetRandomHealth( itemEnt );
			itemEnt = itemClothing.GetInventory().CreateInInventory( "RoadFlare" );
			SetRandomHealth( itemEnt );
			player.SetQuickBarEntityShortcut( itemEnt, 1 );
		}

		// pants
		itemClothing = player.FindAttachmentBySlotName( "Legs" );
		if ( itemClothing )
		{
			SetRandomHealth( itemClothing );

			itemEnt = itemClothing.GetInventory().CreateInInventory( "Heatpack" );
			SetRandomHealth( itemEnt );

			int throwDice = Math.RandomInt( 0, 2 );
			if ( throwDice == 0 )
				itemEnt = itemClothing.GetInventory().CreateInInventory( "dzn_tool_watch" );
			else
				itemEnt = itemClothing.GetInventory().CreateInInventory( "dzn_tool_watch2" );
			player.SetQuickBarEntityShortcut( itemEnt, 2 );
		}

		// shoes
		itemClothing = player.FindAttachmentBySlotName( "Feet" );
		if ( itemClothing )
		{
			SetRandomHealth( itemClothing );
		}

		// bump fresh spawn water and energy values (to compensate for the frozen food and harder-to-get wells)
		player.GetStatWater().Set( 900 );
		player.GetStatEnergy().Set( 1100 );
	}
	// Start of quest init
	override void Expansion_OnQuestStart(ExpansionQuest quest)
	{
		EntityAI itemIn;
		EntityAI itemEnt;
		ItemBase itemBs;
        ExpansionQuestConfig questConfig = quest.GetQuestConfig();
		auto trace = EXTrace.Start(EXTrace.NAMALSKADVENTURE, this);   
        PlayerBase player = quest.GetPlayer();
		 if (!player)
            return;
        switch(questConfig.GetID())
			{
                case 1011:
                {
					SpawnAnimal("Animal_HMG_Bear_Cocaine_T0", Vector(5513.33,117.502,8141.14))
                }
				break;
				case 2000:
                {
					array<vector> Zombiepos = {"4078.74 70.3225 9233.25","4093.89 70.5816 9241.85","4072.58 70.3224 9234.12","4090.79 70.338 9221.54","4064.34 70.4547 9204","4060.72 70.3248 9229.81","4052.09 70.3443 9212.1","4062.03 70.5616 9211.69","4066.02 70.5699 9216.58","4060.82 70.3224 9239.95"};
					int zombiecount = CountZombies(Vector(4078.74, 70.3225, 9233.25), 50)
					for (int i = zombiecount; i < 10; i++)
					{
						SpawnZombie("ZmbM_ruSoldier_normal_Woodland1", Zombiepos[i]);
					}								
                }
				break;
				case 3000:
				{
								
					itemEnt = player.GetInventory().CreateInInventory("Zombie_Samplekit");
								SetFullHealth(itemEnt);
					itemIn = itemEnt.GetInventory().CreateAttachment("Zombie_Blood_Syringe_Empty");
								SetFullHealth(itemIn);
					itemIn = itemEnt.GetInventory().CreateAttachment("Zombie_Blood_Vial_Empty");
								SetFullHealth(itemIn);
					itemIn = itemEnt.GetInventory().CreateAttachment("Zombie_Blood_Vial_Empty");
								SetFullHealth(itemIn);
					itemIn = itemEnt.GetInventory().CreateAttachment("Zombie_Blood_Vial_Empty");
								SetFullHealth(itemIn);												
				}
				break;
				case 5002:
				{
				itemEnt = player.GetInventory().CreateInInventory("PunchedCard");
								SetFullHealth(itemEnt);
				
				SpawnZombie("PITSTOP_Monsters_Syther", Vector(7019.88, 40.2125, 5794.4));	
				}	
			}      
				
	}
		
		override void Expansion_OnQuestCompletion(ExpansionQuest quest)
		{
			EntityAI itemIn;
			EntityAI itemEnt;
			ItemBase itemBs;

		  	ExpansionQuestConfig questConfig = quest.GetQuestConfig();
			auto trace = EXTrace.Start(EXTrace.NAMALSKADVENTURE, this);   
        	PlayerBase player = quest.GetPlayer();
		 if (!player)
            return;
        switch(questConfig.GetID())
		{
			case 3100:
			case 3000:
				{
					/*
					array<vector> teleportPositions1 = {"2000.94 2.01239 9672.32"};
    				vector ori1 = player.GetOrientation();
   					DayZPlayerSyncJunctures.ExpansionTeleport(player, teleportPositions1.GetRandomElement(), ori1);
					*/
					array<vector> teleportPositions1 = {"2000.94 2.01239 9672.32"};
					TeleportPlayer(player ,	teleportPositions1 )
				}
			break;
			case 5001:
				{
					array<vector> teleportPositions2 = {"7095.9 80.5806 6107.36"};
    				TeleportPlayer(player ,	teleportPositions2 )
				}
				break;
				case 5002:
				{
					itemEnt = player.GetInventory().CreateInInventory("PunchedCard");
								SetFullHealth(itemEnt);
				}
		}
		}
	};
	
	void TeleportPlayer(PlayerBase playerT , array<vector> Tpos)
	{
					vector oriT = playerT.GetOrientation();
   					DayZPlayerSyncJunctures.ExpansionTeleport(playerT, Tpos.GetRandomElement(), oriT);

	}

	void SpawnObject( string type, vector position)
	{
		auto obj = GetGame().CreateObject( type, position );
		obj.SetPosition( position );
	}

	void SpawnAnimal(string anmClass , vector anmpos)
	{
		ref array<EntityAI> m_SpawnedAnimals = new array<EntityAI>;
		vector pos = SnapToGround(anmpos);
		EntityAI AIanm = GetGame().CreateObject( anmClass, pos, false, true );
		ref AnimalBase Bsanm;
		Class.CastTo(Bsanm,AIanm);
							// Bszmb.AttachEventHandle(PossibleLootDrops,PossibleWeaponDrops,dropChance); for later use
		m_SpawnedAnimals.Insert(AIanm);
							//  SpawnObject(zmbClass , pos);
	}

	void SpawnZombie(string zmbClass , vector zmbpos)
	{
		ref array<EntityAI> m_SpawnedZombies = new array<EntityAI>;
    	vector pos = SnapToGround(zmbpos);
    	EntityAI AIzmb = GetGame().CreateObject( zmbClass, pos, false, true );
   		ref ZombieBase Bszmb;
    	Class.CastTo(Bszmb,AIzmb);
    		// Bszmb.AttachEventHandle(PossibleLootDrops,PossibleWeaponDrops,dropChance); for later use
    	m_SpawnedZombies.Insert(AIzmb);
    		//  SpawnObject(zmbClass , pos);
    }

	int CountZombies(vector position, float radius)
    {
        array<Object> objects = new array<Object>;
        GetGame().GetObjectsAtPosition(position, radius, objects, null);
        
        int zombieCount = 0;
        
        for (int i = 0; i < objects.Count(); i++)
        {
             if (objects.Get(i).IsInherited(ZombieBase))
        {
            ZombieBase zombie = ZombieBase.Cast(objects.Get(i));
            if (zombie && zombie.IsAlive())
            {
                zombieCount++;
            }
        }
        }
        
        return zombieCount;
    }
void ClearZombies(vector position, float radius)
{
    array<Object> objects = new array<Object>;
    array<CargoBase> proxyCargos = new array<CargoBase>;
    GetGame().GetObjectsAtPosition(position, radius, objects, proxyCargos);
    
    int zombieCount = 0;
    
    for (int i = 0; i < objects.Count(); i++)
    {
        if (objects.Get(i).IsInherited(ZombieBase))
        {
            GetGame().ObjectDelete(objects.Get(i));
            zombieCount++;
        }
    }
    
    Print("Number of zombies cleared from the area: " + zombieCount);
}


  
Mission CreateCustomMission(string path)
{
	return new CustomMission();
};
