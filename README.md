EchoVerse phase-3    https://github.com/Skandar7002/EchoVerse-3

مدل‌سازی ساختار سازمانی تیم تولید پادکست با استفاده از درخت و الگوریتم‌های جستجو

هدف پروژه:

پیاده‌سازی سیستمی برای مدیریت و سازماندهی سلسله مراتب تیم تولید پادکست با استفاده از ساختار درخت و الگوریتم‌های جستجوی BFS و DFS.

مدل مفهومی:
- تیم تولید پادکست = درخت سلسله مراتبی
- هر عضو تیم = گره (Node) در درخت
- رابطه مدیریتی = ارتباط والد-فرزندی
- فرزندان یک مدیر = لیست پیوندی

ساختار گره های درخت:

    struct TeamMember {
        int id;                    // شناسه یکتا
        string name;               // نام عضو
        string role;               // نقش در تیم
        TeamMember* parent;        // اشاره‌گر به والد
        TeamMember* firstChild;    // اشاره‌گر به اولین فرزند
        TeamMember* nextSibling;   // اشاره‌گر به خواهر/برادر بعدی
        };

ساختارهای کمکی:

    // صف برای BFS
    struct QueueNode {
        TeamMember* member;
        QueueNode* next;
    };

    // پشته برای DFS
    struct StackNode {
    TeamMember* member;
    StackNode* next;   
    };

پیاده سازی درخت:

کلاس HierarchyTree (درخت سلسله مراتبی)

متدهای مدیریت اعضا:
1. setRoot(name, role)
- تنظیم رئیس/مدیر اصلی تیم
- فقط یک بار قابل فراخوانی است

2. addMember(parentId, name, role)
- افزودن عضو جدید زیر نظر یک والد
- افزودن به لیست پیوندی فرزندان والد

3. removeMember(id)
- حذف عضو و تمام زیردستانش
- به‌روزرسانی لیست پیوندی والد

متدهای جستجو:
1. bfsSearch(name) (جستجوی سطح‌اول)
- استفاده از صف (Queue)
- مناسب برای یافتن نزدیک‌ترین اعضا

2. dfsSearch(name) (جستجوی عمق‌اول)
- استفاده از پشته (Stack)
- مناسب برای جستجو در عمق ساختار

متدهای نمایش:
- displayTree(): نمایش درخت به صورت سلسله مراتبی

الگوریتم‌های پیاده‌سازی شده:

الگوریتم BFS (Breadth-First Search):

    TeamMember* bfsSearch(const string& name) {

    if (!root) return nullptr;

      enqueue(root);
    
       while (!isQueueEmpty()) {
          TeamMember* current = dequeue();
        
          if (current->name == name) return current;
        
           // اضافه کردن تمام فرزندان به صف
           TeamMember* child = current->firstChild;
           while (child) {
               enqueue(child);
              child = child->nextSibling;
         }
      }
    
     return nullptr;
    }

الگوریتم DFS (Depth-First Search):

    TeamMember* dfsSearch(const string& name) {

    if (!root) return nullptr;
      push(root);
    
      while (!isStackEmpty()) {
           TeamMember* current = pop();
        
          if (current->name == name) return current;
        
            // اضافه کردن فرزندان به پشته
         TeamMember* child = current->firstChild;
         while (child) {
               push(child);
              child = child->nextSibling;
         }
     }
    
     return nullptr;
    }

نمایش درخت به صورت سلسله مراتبی:

    void displayHelper(TeamMember* member, int depth) {
        if (!member) return;

        for (int i = 0; i < depth; i++) {
          cout << "  ";
           if (i == depth - 1) cout << "├─";
        }
    
        member->display();
    
        displayHelper(member->firstChild, depth + 1);
        displayHelper(member->nextSibling, depth);
    }

رابط کاربری با منوی تعاملی:

    === Podcast Production Team Hierarchy ===
    1. Set Root (Team Leader)
    2. Add Team Member
    3. Remove Team Member
    4. Display Team Hierarchy
    5  . Search Member (BFS)
    6. Search Member (DFS)
    7. Auto Test
    8. Exit

نمونه خروجی نمایش درخت:

    === Team Hierarchy ===
    ID: 1, Name: Alice Johnson, Role: Producer, Parent: None
    ├─ID: 2, Name: Bob Smith, Role: Audio Engineer, Parent: Alice Johnson
    │  ├─ID: 4, Name: David Wilson, Role: Sound Designer, Parent: Bob Smith
    │  └─ID: 5, Name: Eva Green, Role: Mixing Engineer, Parent: Bob Smith
    └─ID: 3, Name: Charlie Brown, Role: Content Writer, Parent: Alice Johnson
    ├─ID: 6, Name: Frank Miller, Role: Script Writer, Parent: Charlie Brown
    └─ID: 7, Name: Grace Lee, Role: Researcher, Parent: Charlie Brown

پیچیدگی زمانی:

        عملیات	پیچیدگی	توضیح
    افزودن عضو	O(n)	جستجوی والد + اضافه به لیست
    حذف عضو	O(n)	جستجو + حذف زیردرخت
    BFS Search	O(V + E)	پیمایش تمام گره‌ها و یال‌ها
    DFS Search	O(V + E)	پیمایش تمام گره‌ها و یال‌ها
    نمایش درخت	O(n)	پیمایش پیش‌ترتیب

نتایج تست خودکار:

    === Starting Auto Test ===

    1. Setting root...
        Root set: Alice Johnson (Producer)

    2. Adding team members...
       Added Bob Smith under Alice Johnson
       Added Charlie Brown under Alice Johnson
       Added David Wilson under Bob Smith
       ...

    3. Displaying team hierarchy:
       === Team Hierarchy ===
       ID: 1, Name: Alice Johnson, Role: Producer
       ├─ID: 2, Name: Bob Smith, Role: Audio Engineer
       │  ├─ID: 4, Name: David Wilson, Role: Sound Designer
       │  └─ID: 5, Name: Eva Green, Role: Mixing Engineer
       └─ID: 3, Name: Charlie Brown, Role: Content Writer
       ├─ID: 6, Name: Frank Miller, Role: Script Writer
       └─ID: 7, Name: Grace Lee, Role: Researcher

    4. Searching for 'Grace Lee' with BFS:
       Found: ID: 7, Name: Grace Lee, Role: Researcher, Parent: Charlie Brown

    5. Searching for 'Henry Ford' with DFS:
       Found: ID: 8, Name: Henry Ford, Role: Foley Artist, Parent: David Wilson

    6. Removing member with ID 4...
       Removed member with ID 4

    7. Displaying updated hierarchy...
       === Auto Test Completed ===

ساختار فایل ها:

    PodcastTeamHierarchy/
    ├── TeamMember.h           # رابط ساختار عضو تیم
    ├── TeamMember.cpp         # پیاده‌سازی عضو تیم
    ├── HierarchyTree.h        # رابط کلاس درخت سلسله مراتبی
    ├── HierarchyTree.cpp      # پیاده‌سازی درخت و الگوریتم‌ها
    ├── main.cpp               # رابط کاربری و تست
    ├── README.md              # مستندات پروژه
    

توسعه دهندگان: مجتبی فهیم پور، امیر گریوانی

درس: ساختمان داد ها و الگوریتم