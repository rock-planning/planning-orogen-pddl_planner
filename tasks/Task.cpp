/* Generated from orogen/lib/orogen/templates/tasks/Task.cpp */

#include "Task.hpp"
#include <pddl_planner/PDDLPlanner.hpp>
#include <pddl_planner/planners/Lama.hpp>

using namespace pddl_planner;

Task::Task(std::string const& name, TaskCore::TaskState initial_state)
    : TaskBase(name, initial_state)
    , mPlanner(0)
{
}

Task::Task(std::string const& name, RTT::ExecutionEngine* engine, TaskCore::TaskState initial_state)
    : TaskBase(name, engine, initial_state)
    , mPlanner(0)
{
}

Task::~Task()
{
}

::pddl_planner::PlanCandidates Task::request_plan_candidates(::std::string const & problem)
{
    pddl_planner::PlanCandidates candidates;
    if(!mPlanner)
    {
        return candidates; 
    }

    try {
        candidates = mPlanner->plan(problem);
    } catch(const pddl_planner::PlanGenerationException& e)
    {
        RTT::log(RTT::Warning) << "Plan generation failed: " << e.what() << RTT::endlog();
    }
    return candidates;
}

bool Task::set_action_description(::std::string const & action_name, ::std::string const & description)
{
    if(!mPlanner)
    {
        RTT::log(RTT::Warning) << "Task needs to be configured to enable operation: 'set_action_description'" << RTT::endlog();
        return false;
    }

    mPlanner->setActionDescription(action_name, description);
    return true;
}

bool Task::set_domain_description(::std::string const & domain_name, ::std::string const & description)
{
    if(!mPlanner)
    {
        RTT::log(RTT::Warning) << "Task needs to be configured to enable operation: 'set_domain_description'" << RTT::endlog();
        return false;
    }

    mPlanner->setDomainDescription(domain_name, description);
    return true;
}

/// The following lines are template definitions for the various state machine
// hooks defined by Orocos::RTT. See Task.hpp for more detailed
// documentation about them.

bool Task::configureHook()
{
    if (! TaskBase::configureHook())
        return false;

    // Initialize database of known planners
    pddl_planner::lama::Planner* lamaPlanner = new pddl_planner::lama::Planner();
    mKnownPlanners[lamaPlanner->getName()] = lamaPlanner;

    std::string plannerName = _planner_name.get();

    std::map<std::string, pddl_planner::PDDLPlannerInterface*>::iterator it; 
    it = mKnownPlanners.find(plannerName);

    if( it == mKnownPlanners.end())
    {
        RTT::log(RTT::Error) << "Planner '" << plannerName << "' is unknown" << RTT::endlog();
        return false;
    }

    mPlanner = new pddl_planner::PDDLPlanner(it->second);
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
    delete mPlanner;

    std::map<std::string, pddl_planner::PDDLPlannerInterface*>::iterator it = mKnownPlanners.begin();
    for(;it != mKnownPlanners.end(); ++it)
    {
        delete it->second;
    }
}

