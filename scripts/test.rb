require 'orocos'
include Orocos
Orocos.initialize

Orocos.run 'pddl_planner_test', :wait => 5 do 

    planner = TaskContext.get 'pddl_planner'

    planner.planner_name = "LAMA"
    planner.configure
    planner.start


    domain_description = File.read(File.join(File.dirname(__FILE__),"test-data","test_domain.pddl"))
    problem = File.read(File.join(File.dirname(__FILE__),"test-data","test_problem.pddl"))

    if not planner.set_domain_description("test-domain", domain_description)
        raise "Failed to set domain description"
    else 
        puts "Set description: #{domain_description}"
    end

    candidates = planner.request_plan_candidates(problem)
    puts "Request plan: #{problem}"
    
    puts "Printing plans: "
    candidates.plans.each do |plan|
        puts "# Begin of plan ####"
        plan.action_sequence.each do |action|
            puts "#{action.name}"
            action.arguments.each do |arg|
                puts "\t#{arg}"
            end
        end
        puts "# End of plan ##### "
    end

end
