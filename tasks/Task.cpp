/* Generated from orogen/lib/orogen/templates/tasks/Task.cpp */

#include "Task.hpp"
#include <pddl_planner/Planning.hpp>

using namespace pddl_planner;

Task::Task(std::string const& name, TaskCore::TaskState initial_state)
    : TaskBase(name, initial_state)
    , mPlanning(0)
{
}

Task::Task(std::string const& name, RTT::ExecutionEngine* engine, TaskCore::TaskState initial_state)
    : TaskBase(name, engine, initial_state)
    , mPlanning(0)
{
}

Task::~Task()
{
}

::pddl_planner::PlanCandidates Task::request_plan_candidates(::std::string const & problem)
{
    pddl_planner::PlanCandidates candidates;
    if(!mPlanning)
    {
        return candidates; 
    }

    try {
        candidates = mPlanning->plan(problem);
    } catch(const pddl_planner::PlanGenerationException& e)
    {
        RTT::log(RTT::Warning) << "Plan generation failed: " << e.what() << RTT::endlog();
    }
    return candidates;
}

bool Task::set_action_description(::std::string const & action_name, ::std::string const & description)
{
    if(!mPlanning)
    {
        RTT::log(RTT::Warning) << "Task needs to be configured to enable operation: 'set_action_description'" << RTT::endlog();
        return false;
    }

    mPlanning->setActionDescription(action_name, description);
    return true;
}

bool Task::set_domain_description(::std::string const & domain_name, ::std::string const & description)
{
    if(!mPlanning)
    {
        RTT::log(RTT::Warning) << "Task needs to be configured to enable operation: 'set_domain_description'" << RTT::endlog();
        return false;
    }

    mPlanning->setDomainDescription(domain_name, description);
    return true;
}

/// The following lines are template definitions for the various state machine
// hooks defined by Orocos::RTT. See Task.hpp for more detailed
// documentation about them.

bool Task::configureHook()
{
    if (! TaskBase::configureHook())
        return false;

    mPlanning = new pddl_planner::Planning();

    std::string plannerName = _planner_name.get();
    if(!plannerName.empty())
    {
            // Check if planner is known
        if(mPlanning->isRegistered(plannerName))
        {
            mPlannerName = plannerName;
        } else
        {
            RTT::log(RTT::Error) << this->getName() << ": no planner '" << plannerName << "' is registered" << RTT::endlog();
            return false;
        }
    }

    return true;
}
// bool Task::startHook()
// {
//     if (! TaskBase::startHook())
//         return false;
//     return true;
// }
// void Task::updateHook()
// {
//     TaskBase::updateHook();
// }
// void Task::errorHook()
// {
//     TaskBase::errorHook();
// }
// void Task::stopHook()
// {
//     TaskBase::stopHook();
// }
void Task::cleanupHook()
{
    TaskBase::cleanupHook();
    delete mPlanning;
}

