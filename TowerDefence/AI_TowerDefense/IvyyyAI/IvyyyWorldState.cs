using Agent_System;
using AI_Strategy;
using AI_TowerDefense;
using GameFramework;
using System;
using System.Collections.Generic;
using System.Linq;

namespace IvyyyAI
{
    public class IvyyyWorldState : IvyyyAgentState<IvyyyPerception>
    {
        public int Gold { get; private set; }
        public int TowerCount { get; private set; }
        public int RowCounter { get; set; }

        public Player Player { get; private set; }

        public List <IvyyyPosition> TowerList { get; private set; }
        public List <IvyyyPosition> EnemyList { get; private set; }
        public List <IvyyySoldier> FriendlySoldierList { get; private set; }
        public List <Tower> EnemyTowerList { get; private set; }

        private List<IvyyyTowerBlock> m_towerBlocks;
        private List<IvyyyAttackLane> m_attackLanes;

        public IvyyyPerception.ActionTyp ActionTyp {get; private set;}

        //public methods
        public IvyyyWorldState()
        {
            InitTowerBlocks();
            InitAttackLanes();

            TowerList = new List<IvyyyPosition>();
            EnemyList = new List<IvyyyPosition>();
            EnemyTowerList = new List<Tower>();
            FriendlySoldierList = new List<IvyyySoldier>();

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
            Gold = perception.Player.Gold;
            TowerCount = perception.Player.HomeLane.TowerCount();
            ActionTyp = perception.CurrentActionTyp;
            Player = perception.Player;

            ScaneForUnits(perception);

            for (int i = 0; i < m_towerBlocks.Count; ++i)
                m_towerBlocks[i].Update(EnemyList, TowerList);

            for (int i = 0; i < m_attackLanes.Count; ++i)
                m_attackLanes[i].Update(FriendlySoldierList, EnemyTowerList);
        }

        private void InitTowerBlocks()
        {
            m_towerBlocks = new();

            //Horizontal blocks
            List<IvyyyPosition> towerRelPos = new();
            towerRelPos.Add(new IvyyyPosition(0, 0));
            towerRelPos.Add(new IvyyyPosition(2, 0));
            towerRelPos.Add(new IvyyyPosition(4, 0));
            towerRelPos.Add(new IvyyyPosition(6, 0));

            for (int r = 3; r < PlayerLane.HEIGHT-2; r += 2)
            {
                m_towerBlocks.Add(new IvyyyTowerBlock(0, r));
                m_towerBlocks.Last().SetTowerList(towerRelPos);
            }

            towerRelPos.Clear();

            towerRelPos.Add(new IvyyyPosition(1, 0));
            towerRelPos.Add(new IvyyyPosition(3, 0));
            towerRelPos.Add(new IvyyyPosition(5, 0));

            for (int r = 4; r < PlayerLane.HEIGHT-2; r += 2)
            {
                m_towerBlocks.Add(new IvyyyTowerBlock(0, r));
                m_towerBlocks.Last().SetTowerList(towerRelPos);
            }

            //Vertical blocks
            towerRelPos.Clear();

            towerRelPos.Add(new IvyyyPosition(0, 0));
            towerRelPos.Add(new IvyyyPosition(0, 2));

            for (int c = 0; c < PlayerLane.WIDTH; c += 2)
            {
                for (int r = 4; r < PlayerLane.HEIGHT - 4; r += 2)
                {
                    m_towerBlocks.Add(new IvyyyTowerBlock(c, r));
                    m_towerBlocks.Last().SetTowerList(towerRelPos);
                }
            }
        }

        private void ScaneForUnits(IvyyyPerception perception)
        {
            TowerList.Clear();
            EnemyList.Clear();
            FriendlySoldierList.Clear();
            EnemyTowerList.Clear();

            List<Soldier> enemySoldierList = new();

            //Home Lane
            for (int r = 0; r < PlayerLane.WIDTH; ++r)
            {
                for (int c = 0; c < PlayerLane.HEIGHT; ++c)
                {
                    Unit unit = Player.HomeLane.GetCellAt(r, c).Unit;

                    if (unit is Tower)
                        TowerList.Add(new IvyyyPosition { x = unit.PosX, y = unit.PosY });
                    else if (unit is not null)
                        EnemyList.Add(new IvyyyPosition { x = unit.PosX, y = unit.PosY });
                }
            }

            //Enemy Lane
            for (int r = 0; r < PlayerLane.WIDTH; ++r)
            {
                for (int c = 0; c < PlayerLane.HEIGHT; ++c)
                {
                    Unit unit = Player.EnemyLane.GetCellAt(r, c).Unit;

                    if (unit is Tower)
                        EnemyTowerList.Add(unit as Tower);
                    else if (unit is IvyyySoldier)
                        FriendlySoldierList.Add(unit as IvyyySoldier);
                }
            }
        }

        //Get methods

        private float GetDeploySoldiers(object target)
        {
            return ActionTyp == IvyyyPerception.ActionTyp.DeploySoldiers ? 1f : 0f;
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
            return ActionTyp == IvyyyPerception.ActionTyp.DeployTowers ? 1f : 0f;
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
            return (float)Player.Gold / ((float)attackLane.Width * 2f);
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
            return ((float)TowerCount) / 11f;
        }

        private float GetCanBuyTowers(object target)
        {
            IvyyyTowerBlock block = (IvyyyTowerBlock) target;
            int goldRequired = GetTowerCost(block.TowerSlots.Count - block.TowerCount);

            return Gold >= goldRequired ? 1f : 0f;
        }

        private float GetTargetsInReach(object target)

        {
            IvyyyTowerBlock block = (IvyyyTowerBlock) target;
            int maxTargetCount = block.TowerSlots.Count;
            return (float)block.InReachCount / 3f;
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
