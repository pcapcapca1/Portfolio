/**
  Project Description:
  Information retrieval systems allow users to enter keywords and retrieve articles that have those keywords associated with them.
  For example, once a student named Yi Li wrote a paper called "Object Class Recognition using Images of Abstract Regions"
  and included the following keywords: `object recognition', `abstract regions', `mixture models', and `EM algorithm'.
  If someone does a search for all articles about the EM algorithm, this paper (and many others) will be retrieved.

  Implement a binary search tree and use it to store and retrieve articles. The tree will be sorted by keyword, and each node will
  contain an unordered linked list of Record objects which contain information about each article that corresponds to that
  keyword

  datafile contains the following per Article record
  Title Id
  Title
  Author
  Number of keys identifier
  List of keys in each corresponding article

  Keys are inserted into the Binary Search tree using the insert method in the BST class
  Each key will reference an unordered linked list of article objects (articleid, titleid, and author)

  Algorithm:
    - Create a BufferedReader Object to read the text from an Input stream (datafile.txt) by buffering characters that seamlessly
    reads lines (characters, arrays or lines).
    Note: Each read request made of a Reader causes a corresponding read request to be made of the underlying character or byte stream.
    It wraps BufferedReader in Java around a java FileReaders (whose read() operations may be costly)
    - Loop:
      - read titleid, title, author
        - create an article object
      - read the number of keys identifier
        - Loop read number of keys
          - insert each key into a BST data structure (BST class will insert the key if not exist)
          - add the article object to each of the respective keyword node in the BST data structure

      - output the resultant BST along with the list of articles per keyword
*/
import java.util.LinkedList;
import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.util.Scanner;

public class Project2336F24 {
    public static void main(String args[]) {    
        //Instantiates a binary search tree, storing all the articles and keywords
        BinarySearchTree bst = new BinarySearchTree();
        //Reads the data from the datafile.txt file
        readFileRecords(bst, "datafile.txt");
        
        System.out.println("\t\tWelcome to Information Retrieval System");
       
        Scanner input = new Scanner(System.in);
        int choice;
        //Displays menu options
        do {
            System.out.println("1. InOrder Traversal with Details <Output keywords along with their associated referenced articles.>");
            System.out.println("2. InOrder Traversal (Keywords Only) <Output only the keywords, excluding the referenced articles.>");
            System.out.println("3. PreOrder Traversal (Keywords Only) <Output only the keywords in pre-order traversal, without the referenced articles.> ");
            System.out.println("4. Search for a specific Keyword <If found, display the keyword with referenced articles; otherwise, output the keyword not found message.>");
            System.out.println("5. Exit <Terminates the program.>");
            System.out.print("\nEnter a choice? ");
            choice = input.nextInt();
            input.nextLine(); //Consume newline
            System.out.println();
            //Performs according to whitch choice was made
            switch(choice){
                case 1:
                //Print in order with detail
                    bst.inOrderGivenDetails();
                    break;
                case 2:
                //Print keywords in order 
                    bst.inOrderGivenKeywords();
                    break;
                case 3:
                //Print keywords before in order
                    bst.preOrderGivenKeywords();
                    break;
                //Search for keyword
                case 4:
                    System.out.print("Enter keyword to search: ");
                    String keyword = input.nextLine();
                    bst.keywordSearch(keyword);
                    break;
                //Exit program
                case 5:
                    System.out.println("Exiting program");
                    break;
                //Input validation
                default:
                    System.out.println("Please select a valid choice");
            }
            System.out.println();
        } while (choice != 5);
        //Finish program
        input.close();
    }
    //Reads records from datafile.txt and inserts them into the binary tree
    public static void readFileRecords(BinarySearchTree bst, String filename) {
        BufferedReader fileReader = null;
        try {
            fileReader = new BufferedReader(new FileReader(filename));
        }
        catch (IOException e) {
            e.printStackTrace();
        }
       
        while(true) {
            if (fileReader == null) {
                System.out.println("Error: file must be opened first!");
                break;
            }
            else {
                //Reads details from file
                try {
                    String strId = fileReader.readLine();
                    if (strId == null) break;
                    int id = Integer.parseInt(strId);
                    String title = fileReader.readLine();
                    String author = fileReader.readLine();
                    int numKeys = Integer.parseInt(fileReader.readLine());
                   
                    //Using keywords, insert into BST
                    String keyword;
                    Article art;
                    for (int i=0; i<numKeys; i++) {
                        keyword = fileReader.readLine();
                        art = new Article(id, title, author);
                        bst.insert(keyword, art);
                    }
                   
                    fileReader.readLine();
                }
               
                catch (NumberFormatException e) {
                    e.printStackTrace();
                    break;
                }
                catch (Exception e) {
                    e.printStackTrace();
                    break;
                }
            }
           
        }
       
        //free up resources
        if (fileReader != null) {
            try {
                fileReader.close();
            }
            catch (IOException e) {
                e.printStackTrace();
            }
        }
    }
}

//Binary search tree to manage keywords and their articles
class BinarySearchTree<E extends Comparable<E>> {
    protected TreeNode<E> root;
    protected int size;

    //Search method
    public TreeNode<E> search(E element) {
        TreeNode<E> parent = null;
        TreeNode<E> current = root;
        while (current != null) {
            if (element.compareTo(current.element) < 0) {
                parent = current;
                current = current.leftC;
            } else if (element.compareTo(current.element) > 0) {
                parent = current;
                current = current.rightC;
            } else if (element.compareTo(current.element) == 0) {
                return current;
            }
        }
        return parent;
    }

    //Insert method
    public void insert(E element, Article art) {
        if (root == null) {
            root = new TreeNode<>(element);
            root.head.addFirst(art);
        } else {
            TreeNode<E> parent = search(element);
            if (parent != null) {
                if (element.compareTo(parent.element) < 0) {
                    parent.leftC = new TreeNode<>(element);
                    parent.leftC.head.addFirst(art);
                } else if (element.compareTo(parent.element) > 0) {
                    parent.rightC = new TreeNode<>(element);
                    parent.rightC.head.addFirst(art);
                } else {
                    parent.head.addFirst(art);
                }
            }
        }
        size++;
    }
    
    //Search for specific keyword in binary tree and print out its articles
    public void keywordSearch(E keyword) 
    {
        // Search node using the user keyword
        TreeNode<E> node = search(keyword);
        // If keyword is found, print keyword and articles
        if (node != null && keyword.compareTo(node.element) == 0) 
        {
            System.out.printf("%s\n", node.element);
            for (Article article : node.head) {
                //System.out.println(article);
                System.out.print(article);
            }
        // If keyword doesn't match, print error statement
        } else {
            System.out.println(keyword + " does not exist in the Information Retrieval System!");
        }
    }

    public void inOrder() 
    {
        System.out.println("\n====================================================");
        System.out.println("Running InOrder Traversal of the Binary Search tree:");
        inOrder(root, "", true);
    }
   
    protected void inOrder(TreeNode<E> root, String prefix, boolean isLeft) 
    {
        if (root == null) return;
        inOrder(root.leftC, prefix + (isLeft ? "   " : "    "), true);
        if (root != null) {
            System.out.printf("%s %s %s\n", prefix, (isLeft ? "L " : "R "), root.element);
            for (Article node : root.head)
                System.out.print(node);
            System.out.println();
        }
        inOrder(root.rightC, prefix + (isLeft ? "   " : "    "), false);
    }
    
    //Creates inOrder traversal starting from the very root
    public void inOrderGivenDetails() 
    {
        System.out.println("====================================================");
        System.out.println("Running InOrder Traversal of the Binary Search tree:");
        inOrderWithDetails(root, "", true);
    }

    //Use recursion to traverse and print out article while displaying L or R
    private void inOrderWithDetails(TreeNode<E> root, String prefix, boolean isLeft) 
    {
        if (root == null) return;
        //Traverse through the left subtree
        inOrderWithDetails(root.leftC, prefix + (isLeft ? " " : " "), true);
        //Prints if current node is L or R
        System.out.printf("%s %s %s\n", prefix, (isLeft ? "L " : "R "), root.element);
        for (Article article : root.head) {
            //Print all articles related to the keyword
            System.out.print(article);
        }
        System.out.println();
        //Traverse through the right subtree
        inOrderWithDetails(root.rightC, prefix + (isLeft ? " " : " "), false);
    }

    //Creates a traversal for inOrder (only keywords) for binary tree and starts from beginning
    public void inOrderGivenKeywords() 
    {
        System.out.println("====================================================");
        System.out.println("Running InOrder Traversal of the Binary Search tree:");
        inOrderKeywordsOnly(root, "", true);
        System.out.println();
    }

    //Creates a traversal for preOrder to print only keyword starting from beginning
    public void preOrderGivenKeywords() 
    {
        System.out.println("====================================================");
        System.out.println("Running PreOrder Traversal of the Binary Search tree:");
        preOrderKeywordsOnly(root, "", true);
        System.out.println();
    }

    //Traverse through the tree and print out the keywords with L and R labels 
    private void inOrderKeywordsOnly(TreeNode<E> root, String prefix, boolean isLeft) 
    {
        if (root == null) return;
        //Traverse through left subtree
        inOrderKeywordsOnly(root.leftC, prefix + (isLeft ? " " : " "), true);
        //Print current node with L or R label
        System.out.printf("%s %s %s\n", prefix, (isLeft ? "L" : "R"), root.element);
        //Traverse through right subtree
        inOrderKeywordsOnly(root.rightC, prefix + (isLeft ? " " : " "), false);
    }

    //Pre order traversal, print out the keyword for node, prints out L or R
    private void preOrderKeywordsOnly(TreeNode<E> root, String prefix, boolean isLeft) 
    {
        if (root == null) return;
        //Print current node with L or R label
        System.out.printf("%s %s %s\n", prefix, (isLeft ? "L" : "R"), root.element);
        //Go through left subtree
        preOrderKeywordsOnly(root.leftC, prefix + (isLeft ? " " : " "), true);
        //Go through right subtree
        preOrderKeywordsOnly(root.rightC, prefix + (isLeft ? " " : " "), false);
    }
}

// Node in binary search tree -> left and right
class TreeNode<E> 
{
    protected E element;
    protected TreeNode<E> leftC;
    protected TreeNode<E> rightC;
    protected LinkedList<Article> head;
   
    public TreeNode(E e) {
        element = e;
        head = new LinkedList<Article>();
    }
}

// Article through Id, title, and author
class Article 
{
    private int id;
    private String title;
    private String author;
   
    public Article() { }
    public Article(int i, String t, String a) 
    {
        id = i;
        title = t;
        author = a;
    }
   
    @Override
    public String toString() 
    {
        return String.format("\t %d | %s | %s-->\n", id, title, author);
    }
}
