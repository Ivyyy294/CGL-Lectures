using Agent_System;
using GameFramework;
using System.Collections.Generic;
using System.Linq;

namespace IvyyyAI
{
    public class IvyyyWorldState : IvyyyAgentState<IvyyyPerception>
    {
        public Player Player { get; private set; }

        private int m_gold;
        private int m_towerCount;
        public int RowCounter { get;set;}

        private List <IvyyyPosition> m_towerList;
        private List <IvyyyPosition> m_enemyList;
        private List <IvyyySoldier> m_friendlySoldierList;
        private List<Tower> m_enemyTowerList;

        private List<IvyyyTowerBlock> m_towerBlocks;
        private List<IvyyyAttackLane> m_attackLanes;

        private IvyyyPerception.ActionTyp m_actionTyp;

        //public methods
        public IvyyyWorldState()
        {
            InitTowerBlocks();
            InitAttackLanes();

            m_towerList = new List<IvyyyPosition>();
            m_enemyList = new List<IvyyyPosition>();
            m_enemyTowerList = new List<Tower>();
            m_friendlySoldierList = new List<IvyyySoldier>();

            //Targets
            m_targetMap.Add ("TowerBlocks", m_towerBlocks.ToList<object>());
            m_targetMap.Add ("AttackLanes", m_attackLanes.ToList<object>());

            //Base Stats
            m_actionInputParameters.Add ("DeployTower", GetDeployTower);
            m_actionInputParameters.Add ("TowerCount", GetTowerCount);
            m_actionInputParameters.Add("DeploySoldiers", GetDeploySoldiers);

            //TowerBlock
            m_actionInputParameters.Add ("TargetsInReach", GetTargetsInReach);
            m_actionInputParameters.Add ("FreeTowerSlots", GetFreeTowerSlots);
            m_actionInputParameters.Add ("CanBuyTowers", GetCanBuyTowers);
            m_actionInputParameters.Add ("TowerSpace", GetTowerSpace);

            //AttackLanes
            m_actionInputParameters.Add ("CanBuySoldiers", GetCanBuySoldiers);
            m_actionInputParameters.Add ("LaneRowCounter", GetLaneRowCounter);
            m_actionInputParameters.Add ("LaneFriendlySoldierSpace", GetLaneFriendlySoldierSpace);
            m_actionInputParameters.Add ("LaneSuccessFactor", GetLaneSuccessFactor);
            m_actionInputParameters.Add ("CanBuyRegiment", GetCanBuyRegiment);
        }

        //Private methods
        private void InitAttackLanes()
        {
            //Init Attack Lanes
            m_attackLanes = new();

            InitAttackLane(4);
            InitAttackLane(5);
            InitAttackLane(6);
            InitAttackLane(7);
        }

        private void InitAttackLane(int width)
        {
            for (int c = 0; c + width - 1 < PlayerLane.WIDTH; c++)
                m_attackLanes.Add(new IvyyyAttackLane(c, width, 9));
        }

        public override void Update(IvyyyPerception perception)
        {
            m_gold = perception.Player.Gold;
            m_towerCount = perception.Player.HomeLane.TowerCount();
            m_actionTyp = perception.CurrentActionTyp;
            Player = perception.Player;

            ScaneForUnits(perception);

            for (int i = 0; i < m_towerBlocks.Count; ++i)
                m_towerBlocks[i].Update(m_enemyList, m_towerList);

            for (int i = 0; i < m_attackLanes.Count; ++i)
                m_attackLanes[i].Update(m_friendlySoldierList, m_enemyTowerList);
        }

        private void InitTowerBlocks()
        {
            m_towerBlocks = new();
            List<IvyyyPosition> towerRelPos = new();

            //Horizontal blocks
            towerRelPos.Add(new IvyyyPosition(0, 0));
            towerRelPos.Add(new IvyyyPosition(2, 0));
            towerRelPos.Add(new IvyyyPosition(4, 0));
            towerRelPos.Add(new IvyyyPosition(6, 0));

            for (int r = 3; r < PlayerLane.HEIGHT - 2; r += 2)
            {
                m_towerBlocks.Add(new IvyyyTowerBlock(0, r));
                m_towerBlocks.Last().SetTowerList(towerRelPos);
            }

            towerRelPos.Clear();

            towerRelPos.Add(new IvyyyPosition(1, 0));
            towerRelPos.Add(new IvyyyPosition(3, 0));
            towerRelPos.Add(new IvyyyPosition(5, 0));

            for (int r = 4; r < PlayerLane.HEIGHT - 2; r += 2)
            {
                m_towerBlocks.Add(new IvyyyTowerBlock(0, r));
                m_towerBlocks.Last().SetTowerList(towerRelPos);
            }

            //Star blocks
            towerRelPos.Clear();

            towerRelPos.Add(new IvyyyPosition(0, 0));
            towerRelPos.Add(new IvyyyPosition(1, 1));
            towerRelPos.Add(new IvyyyPosition(2, 0));

            for (int c = 0; c < PlayerLane.WIDTH - 1; c += 2)
            {
                for (int r = 3; r < PlayerLane.HEIGHT - 2; r += 2)
                {
                    m_towerBlocks.Add(new IvyyyTowerBlock(c, r));
                    m_towerBlocks.Last().SetTowerList(towerRelPos);
                }
            }

            towerRelPos.Clear();

            towerRelPos.Add(new IvyyyPosition(0, 0));
            towerRelPos.Add(new IvyyyPosition(1, 1));
            towerRelPos.Add(new IvyyyPosition(0, 2));

            for (int c = 0; c < PlayerLane.WIDTH - 1; c += 2)
            {
                for (int r = 3; r < PlayerLane.HEIGHT - 3; r += 2)
                {
                    m_towerBlocks.Add(new IvyyyTowerBlock(c, r));
                    m_towerBlocks.Last().SetTowerList(towerRelPos);
                }
            }

            towerRelPos.Clear();

            towerRelPos.Add(new IvyyyPosition(1, 0));
            towerRelPos.Add(new IvyyyPosition(0, 1));
            towerRelPos.Add(new IvyyyPosition(1, 2));

            for (int c = 1; c < PlayerLane.WIDTH - 1; c += 2)
            {
                for (int r = 3; r < PlayerLane.HEIGHT - 3; r += 2)
                {
                    m_towerBlocks.Add(new IvyyyTowerBlock(c, r));
                    m_towerBlocks.Last().SetTowerList(towerRelPos);
                }
            }
        }

        private void ScaneForUnits(IvyyyPerception perception)
        {
            m_towerList.Clear();
            m_enemyList.Clear();
            m_friendlySoldierList.Clear();
            m_enemyTowerList.Clear();

            List<Soldier> enemySoldierList = new();

            //Home Lane
            for (int r = 0; r < PlayerLane.WIDTH; ++r)
            {
                for (int c = 0; c < PlayerLane.HEIGHT; ++c)
                {
                    Unit unit = Player.HomeLane.GetCellAt(r, c).Unit;

                    if (unit is Tower)
                        m_towerList.Add(new IvyyyPosition { x = unit.PosX, y = unit.PosY });
                    else if (unit is not null)
                        m_enemyList.Add(new IvyyyPosition { x = unit.PosX, y = unit.PosY });
                }
            }

            //Enemy Lane
            for (int r = 0; r < PlayerLane.WIDTH; ++r)
            {
                for (int c = 0; c < PlayerLane.HEIGHT; ++c)
                {
                    Unit unit = Player.EnemyLane.GetCellAt(r, c).Unit;

                    if (unit is Tower)
                        m_enemyTowerList.Add(unit as Tower);
                    else if (unit is IvyyySoldier)
                        m_friendlySoldierList.Add(unit as IvyyySoldier);
                }
            }
        }

        //Get methods

        private float GetDeploySoldiers(object target)
        {
            return m_actionTyp == IvyyyPerception.ActionTyp.DeploySoldiers ? 1f : 0f;
        }

        private float GetTowerSpace(object target)
        {
            IvyyyTowerBlock block = (IvyyyTowerBlock)target;
            return (float)block.TowerSlots.Count / 4f;
        }

        private float GetLaneSuccessFactor(object target)
        {
            IvyyyAttackLane attackLane = (IvyyyAttackLane)target;

            if (attackLane.EnemyTowerCount == 0)
                return 1f;

            float val =  (attackLane.Width * attackLane.Depth) / ((float)attackLane.EnemyTowerCount * 10f);

            return val;
        }

        private float GetDeployTower(object target)
        {
            return m_actionTyp == IvyyyPerception.ActionTyp.DeployTowers ? 1f : 0f;
        }

        public int GetTowerCost (int amount = 1)
        {
            int cost = Tower.GetNextTowerCosts (Player.HomeLane);
            int count = Player.HomeLane.TowerCount() + 1;

            for (int i = 1; i < amount; ++i, count++)
                cost += Tower.COSTS + count;

            return cost;
        }

        private float GetCanBuySoldiers(object target)
        {
            IvyyyAttackLane attackLane = (IvyyyAttackLane)target;
            if (Player.Gold >= attackLane.Width * 2)
                return 1f;
            else
                return 0f;
        }

        private float GetCanBuyRegiment(object target)
        {
            IvyyyAttackLane attackLane = (IvyyyAttackLane)target;
            return (float)Player.Gold / attackLane.RequierdGold;
        }

        private float GetLaneRowCounter(object target)
        {
            IvyyyAttackLane attackLane = (IvyyyAttackLane)target;
            
            return (float)RowCounter / (float)attackLane.Depth;
        }

        private float GetTowerCount(object target)
        {
            return ((float)m_towerCount) / 8f;
        }

        private float GetCanBuyTowers(object target)
        {
            IvyyyTowerBlock block = (IvyyyTowerBlock) target;
            int goldRequired = GetTowerCost(block.TowerSlots.Count - block.TowerCount);

            return m_gold >= goldRequired ? 1f : 0f;
        }

        private float GetTargetsInReach(object target)

        {
            IvyyyTowerBlock block = (IvyyyTowerBlock) target;
            int maxTargetCount = block.TowerSlots.Count;
            return (float)block.InReachCount / 35f;
        }

        //Tower
        private float GetFreeTowerSlots(object target)
        {
            IvyyyTowerBlock block = (IvyyyTowerBlock) target;

            int count = 0;

            foreach (var item in block.TowerSlots)
            {
                if (Player.HomeLane.GetCellAt(item.x, item.y).Unit != null)
                    ++count;
            }

            return (block.TowerSlots.Count - count) / block.TowerSlots.Count;
        }

        private float GetLaneFriendlySoldierSpace(object target)
        {
            IvyyyAttackLane attackLane = (IvyyyAttackLane)target;

            return ((float)attackLane.Width) / (float)PlayerLane.WIDTH;
        }
    }
}
