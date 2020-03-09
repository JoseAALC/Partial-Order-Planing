#ifndef ACTION_HPP
#define ACTION_HPP
#include "Predicate.hpp"
#include <string>
#include <vector>
#include <unordered_set>


/**
 * class that represents an action of plan
 */
class Action{
  public:
   ~Action();
    Action(std::vector<Predicate*> pre_condictions,std::vector<Predicate*> result,Predicate* params);
    
    std::vector<Predicate*> getPre_Condiction() const;

    std::vector<Predicate*> getResult() const;

    Predicate* getParams() const;

    bool operator<(const Action& other) const;

    operator std::string() const;
    
    /**
     * @brief checks if an precondiction is solved
     * 
     * @param index of precondiction to check
     * @return true if is false otherwise
     */
    bool getSolved(int index);
   /**
     * @brief set an precondiction as solved
     * 
     * @param index of precondiction to set
     */
    void setSolved(int index);

    Action* copy(Bindings* binds) const;

    int getId();

    /**
     * @brief search for a specific precondiction 
     *
     * 
     * @param id , for the precondiction we want
     * @return the precondiction with this id
     */
    Predicate* searchPrecondiction(int id);

    /**
     * @brief the id generator returns to zero
     * 
     */
    static void resetIds();
    
  protected:
  private:
    /**
     * precondictions list
     */
    vector<Predicate*> pre_condictions;
    /**
     * post condictions list
     */
    vector<Predicate*> result;
    /**
     * params of action
     */
    Predicate* params;
    /**
     * list of solvebility of precondictions
     */
    vector<int> is_solved;
    /**
     * variable responsible to give ids
     */
    static int  idGiver;
    /**
     * id of action
     */
    int id;
};
#endif


