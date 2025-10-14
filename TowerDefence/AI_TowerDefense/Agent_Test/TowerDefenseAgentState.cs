using Agent_System;
using GameFramework;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Agent_Test
{
    public class TowerDefenseAgentState : AgentState<TowerDefensePerception>
    {
        public int Gold { get; private set; }
        public int TowerCount { get; private set; }
        public int EnemyCount { get; private set; }
        public int RegimentCounter { get; set;}

        public TowerDefensePerception.ActionTyp ActionTyp {get; private set;}

        public override void Update(TowerDefensePerception perception)
        {
            Gold = perception.Player.Gold;
            TowerCount = perception.Player.HomeLane.TowerCount();
            EnemyCount = perception.Player.HomeLane.SoldierCount();
            ActionTyp = perception.CurrentActionTyp;
        }
    }
}
