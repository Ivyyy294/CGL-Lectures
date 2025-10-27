using Agent_System;
using AI_TowerDefense;
using GameFramework;
using System;
using System.Collections.Generic;
using System.Linq;

namespace AI_Strategy
{
    public class TowerDefensePerimeter
    {
        int m_startX;
        int m_startY;
        int m_colums;
        int m_rows;

        public int SoldierCount { get; private set;}
        public int TowerCount { get; private set;}
        public int ThreatenedCount { get; private set; }
        public int InReachCount { get; private set; }
        public float RatingLevel { get; private set; }

        public int X => m_startX;
        public int Y => m_startY;

        public TowerDefensePerimeter (int x, int y, int c, int r)
        {
            m_startX = x;
            m_startY = y;
            m_colums = c;
            m_rows = r;
        }

        public void Update (List<IvyyyPosition> enemyList, List<IvyyyPosition> towerList)
        {
            SoldierCount = 0;
            TowerCount = 0;
            ThreatenedCount = 0;
            InReachCount = 0;
            RatingLevel = 0;

            foreach (var enemy in enemyList)
            {
                if (IsPosInside (enemy))
                    SoldierCount++;
                else if (IsPosInside(enemy, 1))
                {
                    InReachCount++;
                    ThreatenedCount++;
                }
                else if (IsPosInside(enemy, 2))
                    InReachCount++;
            }

            foreach (var tower in towerList)
            {
                if (IsPosInside (tower))
                    TowerCount++;
            }

            SetRatingLevel();
        }

        private bool IsPosInside (IvyyyPosition pos, int padding = 0)
        {
            if (pos.x < m_startX - padding || pos.x > m_startX + m_colums + padding
                || pos.y < m_startY - padding || pos.y > m_startY + m_rows + padding)
                return false;
            else
                return true;
        }

        private void SetRatingLevel ()
        {
            RatingLevel = ThreatenedCount + SoldierCount * 1.5f + TowerCount * 0.5f - InReachCount * 1.5f ;
        }
    }

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

        private List<TowerDefensePerimeter> m_defensePerimeter;

        public TowerDefensePerimeter BestDefensePerimeter { get; set; }

        public TowerDefensePerception.ActionTyp ActionTyp {get; private set;}

        public ActiveRegimentSettings ActiveRegimentSettings { get; set; }

        //Enemy Spawn
        public TowerDefenseAgentState()
        {
            ActiveRegimentSettings = null;
            m_defensePerimeter = new ();

            for (int r = 3; r < PlayerLane.HEIGHT - 1; r += 2)
            {
                for (int c = 0; c < PlayerLane.WIDTH - 1; c += 2)
                    m_defensePerimeter.Add(new TowerDefensePerimeter(c, r, 3, 3));
            }

            List<object> test = m_defensePerimeter.ToList<object>();

            TowerList = new List<IvyyyPosition>();
            EnemyList = new List<IvyyyPosition>();

            //ActionInputParameters
            m_targetMap.Add ("TowerField", m_defensePerimeter.ToList<object>());
            m_targetMap.Add ("EnemySoldiers", new());
            m_actionInputParameters.Add ("NoEnemyActive", GetNoEnemyActive);
            m_actionInputParameters.Add ("NoTowerActive", GetNoTowerActive);
            m_actionInputParameters.Add ("StartPhase", GetStartPhase);
            m_actionInputParameters.Add ("DeployTowers", GetDeployTowers);
            m_actionInputParameters.Add ("DeploySoldiers", GetDeploySoldiers);
            m_actionInputParameters.Add ("ActiveRegimentSettings", GetActiveRegimentSettings);
            m_actionInputParameters.Add ("RegimentComplete", GetRegimentComplete);
            m_actionInputParameters.Add ("CanBuySoldiers", GetCanBuySoldiers);
            m_actionInputParameters.Add ("CanBuyTowers", GetCanBuyTowers);
            m_actionInputParameters.Add ("ValidTowerSpot", GetValidTowerSpot);
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

            for (int i = 0; i < m_defensePerimeter.Count; ++i)
                m_defensePerimeter[i].Update(EnemyList, TowerList);

            if (EnemyCount == 0)
                BestDefensePerimeter = new TowerDefensePerimeter (2, 3, 3, 3);
            else
            {
                m_defensePerimeter = m_defensePerimeter.OrderBy (x=>x.RatingLevel).ToList();
                BestDefensePerimeter = m_defensePerimeter[0];
            }
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
            if (BestDefensePerimeter.TowerCount == 4)
                return 0f;

            int goldRequired = GetTowerCost(4 - BestDefensePerimeter.TowerCount);

            return Gold >= goldRequired ? 1f : 0f;
        }

        private float GetValidTowerSpot(object target)
        {
            return BestDefensePerimeter.InReachCount == 0 ? 0f : 1f;
        }

        private float GetDeploySoldiers(object target)
        {
            return ActionTyp == TowerDefensePerception.ActionTyp.DeploySoldiers ? 1f : 0f;
        }
    }
}
