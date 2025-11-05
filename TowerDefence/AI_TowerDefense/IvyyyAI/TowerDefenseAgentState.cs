using Agent_System;
using AI_TowerDefense;
using GameFramework;
using System;
using System.Collections.Generic;
using System.Linq;

namespace AI_Strategy
{
    public class TowerDefenseAgentState : AgentState<TowerDefensePerception>
    {
        public int Gold { get; private set; }
        public int TowerCount { get; private set; }
        public int EnemyCount { get; private set; }
        public int SoldierCount { get; private set; }
        public int RegimentCounter { get; set;}
        public Player Player { get; private set; }

        public List <IvyyyPosition> TowerList { get; private set; }
        public List <IvyyyPosition> EnemyList { get; private set; }

        private List<IvyyyTowerBlock> m_towerBlocks;

        public TowerDefensePerception.ActionTyp ActionTyp {get; private set;}

        public ActiveRegimentSettings ActiveRegimentSettings { get; set; }

        //Enemy Spawn
        public TowerDefenseAgentState()
        {
            ActiveRegimentSettings = new ActiveRegimentSettings();
            m_towerBlocks = new ();

            List<IvyyyPosition> towerRelPos = new();
            towerRelPos.Add(new IvyyyPosition(1, 0));
            towerRelPos.Add(new IvyyyPosition(1, 2));
            towerRelPos.Add(new IvyyyPosition(0, 1));
            towerRelPos.Add(new IvyyyPosition(2, 1));

            for (int r = 3; r < PlayerLane.HEIGHT - 1; r += 2)
            {
                for (int c = 0; c < PlayerLane.WIDTH - 1; c += 2)
                {
                    m_towerBlocks.Add(new IvyyyTowerBlock(c, r, 3, 3));
                    m_towerBlocks.Last().SetTowerList(towerRelPos);
                }
            }

            TowerList = new List<IvyyyPosition>();
            EnemyList = new List<IvyyyPosition>();

            //ActionInputParameters
            m_targetMap.Add ("TowerBlocks", m_towerBlocks.ToList<object>());
            m_targetMap.Add ("EnemySoldiers", new());
            m_actionInputParameters.Add ("NoEnemyActive", GetNoEnemyActive);
            m_actionInputParameters.Add ("NoTowerActive", GetNoTowerActive);
            m_actionInputParameters.Add ("StartPhase", GetStartPhase);
            m_actionInputParameters.Add ("DeployTowers", GetDeployTowers);
            m_actionInputParameters.Add ("DeploySoldiers", GetDeploySoldiers);
            m_actionInputParameters.Add ("CanBuySoldiers", GetCanBuySoldiers);

            //Regiment
            m_actionInputParameters.Add ("RegimentComplete", GetRegimentComplete);
            m_actionInputParameters.Add ("ActiveRegimentSettings", GetActiveRegimentSettings);

            //TowerBlock
            m_actionInputParameters.Add ("ThreatenedCount", GetThreatenedCount);
            m_actionInputParameters.Add ("EnemyInBlockCount", GetEnemyInBlockCount);
            m_actionInputParameters.Add ("TargetsInReach", GetTargetsInReach);
            m_actionInputParameters.Add ("FreeTowerSlots", GetFreeTowerSlots);
            m_actionInputParameters.Add ("CanBuyTowers", GetCanBuyTowers);
        }

        public override void Update(TowerDefensePerception perception)
        {
            Gold = perception.Player.Gold;
            TowerCount = perception.Player.HomeLane.TowerCount();
            EnemyCount = perception.Player.HomeLane.SoldierCount();
            ActionTyp = perception.CurrentActionTyp;
            Player = perception.Player;
            SoldierCount = perception.Player.EnemyLane.SoldierCount();

            ScaneForUnits (perception);

            for (int i = 0; i < m_towerBlocks.Count; ++i)
                m_towerBlocks[i].Update(EnemyList, TowerList);
        }

        public int GetTowerCost (int amount = 1)
        {
            int cost = Tower.GetNextTowerCosts (Player.HomeLane);
            int count = Player.HomeLane.TowerCount() + 1;

            for (int i = 1; i < amount; ++i, count++)
                cost += Tower.COSTS + count;

            return cost;
        }

        private void ScaneForUnits (TowerDefensePerception perception)
        {
            m_targetMap["EnemySoldiers"].Clear();
            TowerList.Clear();
            EnemyList.Clear();

            List<Soldier> enemySoldierList = new();

            for (int r = 0; r < PlayerLane.WIDTH; ++r)
            {
                for (int c = 0; c < PlayerLane.HEIGHT; ++c)
                {
                    Unit unit = Player.HomeLane.GetCellAt(r, c).Unit;

                    if (unit is Tower)
                        TowerList.Add(new IvyyyPosition { x = unit.PosX, y = unit.PosY });
                    else if (unit is not null)
                    {
                        EnemyList.Add(new IvyyyPosition{ x = unit.PosX, y = unit.PosY});
                        m_targetMap["EnemySoldiers"].Add (enemySoldierList);
                    }
                }
            }
        }

        //Get methods
        private float GetNoEnemyActive (object target)
        {
            return EnemyCount > 0 ? 0f : 1f;
        }

        private float GetNoTowerActive(object target)
        {
            return TowerCount > 0 ? 0f : 1f;
        }

        private float GetStartPhase(object target)
        {
            return TowerDefense.Instance.Turns < 10 ? 1.0f : 0f;
        }

        private float GetDeployTowers(object target)
        {
            return ActionTyp == TowerDefensePerception.ActionTyp.DeployTowers ? 1.0f : 0f;
        }

        private float GetActiveRegimentSettings(object target)
        {
            return ActiveRegimentSettings == null ? 1f : 0f;

            //bool upgrade = Gold > ActiveRegimentSettings.Depth * (ActiveRegimentSettings.Width + 1) * 2;
            //bool downgrade = Gold < (ActiveRegimentSettings.Width - 1) * 2;

            //return (upgrade
            //    || downgrade) ? 1f : 0f;
        }

        private float GetRegimentComplete(object target)
        {
            if (ActiveRegimentSettings == null)
                return 0f;
            return ActiveRegimentSettings.IsRegimentComplete() ? 1f : 0f;
        }

        private float GetCanBuySoldiers(object target)
        {
            if (ActiveRegimentSettings == null
                || ActiveRegimentSettings.IsRowComplete (0))
                return 0f;

            return Gold >= ActiveRegimentSettings.Width * 2f ? 1f : 0f;
        }

        private float GetCanBuyTowers(object target)
        {
            IvyyyTowerBlock block = (IvyyyTowerBlock) target;
            int goldRequired = GetTowerCost(5 - block.TowerCount);

            return Gold >= goldRequired ? 1f : 0f;
        }

        private float GetTargetsInReach(object target)
        {
            IvyyyTowerBlock block = (IvyyyTowerBlock) target;
            return block.InReachCount / 24f;
        }

        private float GetDeploySoldiers(object target)
        {
            return ActionTyp == TowerDefensePerception.ActionTyp.DeploySoldiers ? 1f : 0f;
        }

        //Tower
        private float GetFreeTowerSlots(object target)
        {
            IvyyyTowerBlock block = (IvyyyTowerBlock) target;

            int count = 0;

            foreach ( var item in block.TowerSlots )
            {
                if (Player.HomeLane.GetCellAt (item.x, item.y).Unit == null)
                    ++count;
            }

            return (float)count / 4f;
        }

        private float GetThreatenedCount(object target)
        {
            IvyyyTowerBlock block = (IvyyyTowerBlock)target;

            if (block.ThreatenedCount >= 16)
                return 0f;

            return 16f / (16f - (float)block.ThreatenedCount);
        }

        private float GetEnemyInBlockCount(object target)
        {
            IvyyyTowerBlock block = (IvyyyTowerBlock)target;
            return 9f / (9f - block.SoldierCount);
        }
    }
}
