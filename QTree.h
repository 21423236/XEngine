#ifndef __QTREE__
#define __QTREE__

/*************************************
�����Ĳ���
��Ҷ�ӽڵ��⣬ÿ���ڵ㶼���ĸ����ӡ�
ֻ��Ҷ�ӽڵ��ܰ���ʵ��ڵ㣨���꣩��
�������������м�ڵ㣬���ĸ����Ӷ���û�б���ʵ���Ҷ�ӽڵ㡣
�˴���ʵ��ڵ���ecs������ʵ���������Ϣ��
ʵ�ֻ������������ɾ����
entity�ƶ�ʱ��������������������ʵ��λ�������еĸ��¡�
**************************************/
#include "PreHeader.h"
#include "Geometry.h"

struct QTreePos : public Position
{
    Rect    preArea;
    void    *entity;

    QTreePos(float _x = 0.0f, float _y = 0.0f, void *e = nullptr):Position(_x, _y),
        entity(e)
    {

    }

    QTreePos(Position pos, void *e = nullptr):Position(pos),
        entity(e)
    {

    }

    bool operator == (const QTreePos &pos) const
    {
        return x == pos.x && y == pos.y;
    }

    bool IsInPreArea()
    {
        return preArea.is_contain(*this);
    }

    void Update(Position pos)
    {
        x = pos.x;
        y = pos.y;
    }
};

class QTree         //�Ĳ�����
{
private:
    enum Direct
    {
        lu = 0,
        ru = 1,
        rd = 2,
        ld = 3
    };

    struct Node
    {
        typedef std::vector<QTreePos*> Entities;
        typedef std::size_t Count;

        Count count;
        Rect area;
        Entities entitys;   //ʵ������꣬������ʵ���ƶ�������ֻ�ǳ���һ�������ָ�룬��������������
        Node * sub_area[4];
        Node * parent;		//ָ���׵�ָ�룬���ڵ�ʱ����õ�

        Node(const Rect &, Node *, Count c = 4);
        ~Node();

        //������������ʾ���Ϊ��������
        bool is_leaf() const
        {
            return sub_area[lu] == nullptr &&
                sub_area[ru] == nullptr &&
                sub_area[rd] == nullptr &&
                sub_area[ld] == nullptr;
        }

        bool is_full() const
        {
            return count < entitys.size();
        }

        bool is_empty() const
        {
            return entitys.size() == 0;
        }

        Entities::iterator find_entity(const QTreePos &pos)
        {
            for(auto it = entitys.begin(); it != entitys.end(); ++it)
            {
                if(pos == **it)
                {
                    return it;
                }
            }
            return entitys.end();
        }

        void erase_entity(const Entities::iterator &it)
        {
            entitys.erase(it);
            delete *it;
        }
    };

    Node *root;
public:
    QTree(const Rect &);
    ~QTree();

    //�������нڵ�����꣬���ܻ��������ɾ��������һ֡һ��
    void Update();

    //����һ���ڵ�
    void insert(QTreePos *);

    //ɾ��һ���ڵ�
    void remove(QTreePos *);

    //�����ҵ��Ľڵ�����
    std::vector<QTreePos> findInRect(const Rect &rt);
private:
    void Update(Node *);

    void insert(QTreePos *, Node &);
    void remove(QTreePos *, Node &);
    void find_in_node(const Node &, const Rect &, std::vector<QTreePos> &);
    void adjust(Node &);	//ɾ���������ܳ����ĸ�Ҷ�Ӷ�û�б���ʵ�壬�ô˺������� 

    Rect cut_rect(const Rect &rec, const Direct dir)
    {
        QTreePos center((rec.lu.x + rec.rd.x)/2, (rec.lu.y + rec.rd.y)/2);
        switch (dir)
        {
        case lu:
            return Rect(rec.lu, center);
        case ru:
            return Rect(QTreePos(center.x, rec.lu.y), QTreePos(rec.rd.x, center.y));
        case rd:
            return Rect(center, rec.rd);
        case ld:
            return Rect(QTreePos(rec.lu.x, center.y), QTreePos(center.x, rec.rd.y));
        }
    }
};

#endif