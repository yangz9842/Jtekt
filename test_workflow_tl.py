import os
import sys
import time

from btc_embedded import (EPRestApi, get_merged_config, get_vector_gen_config,
                          util)


def run_btc_test(epp_file):
    epp_file = os.path.abspath(epp_file)
    work_dir = os.path.dirname(epp_file)
    report_dir = os.path.abspath(f"{work_dir}/reports")
    if not os.path.exists(report_dir):
        os.makedirs(report_dir)
    #test_config_abs_path = os.path.abspath('C:\Restapitraining\Toyota\btc_project_config.yml')
    #config = get_merged_config(project_directory=os.path.dirname('C:/Restapitraining/Toyota/'))
    #config = get_merged_config(project_directory=work_dir)
    # BTC EmbeddedPlatform API object
    #ep = EPRestApi(config=config)
    ep = EPRestApi()
    ep.delete("")
    print("Step 1 creating profile and importing TL Architecture")
    firststart = time.time()
    #create a new TargetLink profile
    ep.post('profiles?discardCurrentProfile=true')
    tl_payload = {
        'tlModelFile': 'C:\Test\Jtekt\powerwindow_tl.slx',
        'tlInitScript': 'C:\Test\Jtekt\powerwindow_tl_init.m',
        'calibrationHandling': 'EXPLICIT_PARAMETER'
    }
    ep.post('architectures/targetlink',tl_payload,message='importing architecture')
    end = time.time()
    print("Step 1 completed")
    print("Duration (in seconds): ")
    print(end - firststart)
    print('\n')
    # Load a BTC EmbeddedPlatform profile (*.epp)
    #ep.get(f"profiles/{epp_file}?discardCurrentProfile=true", message="Loading profile")
    
    # Update architecture (incl. code generation via TL)
    # (arch-update fails when profile is dirty: EP-2752 -> saving it, to be on the safe side)
    #ep.put('profiles', { 'path': epp_file })
    #ep.put('architectures', message='Updating architecture')

    # Execute requirements-based tests on MIL and SIL
    print("Step 2 generating Vectors")
    start = time.time()
    scopes = ep.get('scopes')
    scope_uids = [ scope['uid'] for scope in scopes if scope['architecture'] == 'TargetLink' ]
    toplevel_scope_uid = scope_uids[0]
    #rbt_exec_payload = {
    #    'UIDs': scope_uids,
    #    'data' : {
    #        'execConfigNames' : [ 'TL MIL', 'SIL' ]
    #    }
    #}
    #response = ep.post('scopes/test-execution-rbt', rbt_exec_payload, message="Executing requirements-based tests")
    #rbt_coverage = ep.get(f"scopes/{toplevel_scope_uid}/coverage-results-rbt?goal-types=MCDC")
    #util.print_rbt_results(response, rbt_coverage)

    # automatic test generation
    # vector_gen_config = get_vector_gen_config(toplevel_scope_uid, config)
    # not using any config due to set preferences
    # vector_gen_config = get_toyota_vector_gen_config(toplevel_scope_uid)
    toplevel_scope_uid = scopes[0]['uid']

    engine_setting = { 'scopeUid' : toplevel_scope_uid,
                    
                      'pllString': 'MCDC',
                      'engineSettings' : {
                          'timeoutSeconds' : 480 
                          }
                  }

    ep.post('coverage-generation', engine_setting)
   # ep.post('coverage-generation', vector_gen_config, message="Generating vectors")
    b2b_coverage = ep.get(f"scopes/{toplevel_scope_uid}/coverage-results-b2b?goal-types=MCDC")
    end = time.time()
    print("Step 2 completed")
    print("Duration (in seconds): ")
    print(end - start)
    print('\n')

    # B2B TL MIL vs. SIL
    print("Step 3 performing a B2B test")
    start = time.time()
    response = ep.post(f"scopes/{toplevel_scope_uid}/b2b", { 'refMode': 'TL MIL', 'compMode': 'SIL' }, message="Executing B2B test")
    b2b_uid = response['uid']
    util.print_b2b_results(response, b2b_coverage)
    end = time.time()
    print("Step 3 completed")
    print("Duration (in seconds): ")
    print(end - start)
    
    print("Step 4 creating reports")
    start = time.time()
    # create code analysis report
    report = ep.post(f"scopes/{toplevel_scope_uid}/code-analysis-reports-b2b", message="Creating code analysis report")
    # export the report
    ep.post(f"reports/{report['uid']}", { 'exportPath': report_dir, 'newName': 'code_analysis' })
    
    # create the B2B-report
    report = ep.post(f"b2b/{b2b_uid}/b2b-reports", message="Creating b2b report")
    # export the report
    ep.post(f"reports/{report['uid']}", { 'exportPath': report_dir, 'newName': 'b2b_report' })
    
    # get b2b-reports
    # b2b/{b2b-test-uid}/b2b-reports
    # Create project report
    report = ep.post(f"scopes/{toplevel_scope_uid}/project-report", message="Creating test report")
    # export project report to a file called 'report.html'
    ep.post(f"reports/{report['uid']}", { 'exportPath': report_dir, 'newName': 'project_report' })
    end = time.time()
    print("Step 4 completed")
    print("Duration (in seconds): ")
    print(end - start)
    
    print("Saving profile.")
    # Save *.epp
    ep.put('profiles', { 'path': epp_file }, message="Saving profile")

    print('Finished with workflow.')
    print("Complete workflow duration (in minutes): ")
    print((end - firststart)/60)
    print("Shutting down")


# Allows the script to be called directly
# (e.g., "python.exe test_workflow.py some_folder/my_project.epp")
if __name__ == '__main__':
    run_btc_test('C:\Restapitraining\Toyota\pw.epp')


def get_toyota_vector_gen_config(scope_uid,config):
    vector_generation_config = { 'scopeUid' : scope_uid }
    # engine settings
    engine_settings = {}
    cv_settings = { 'name' : 'CV' }
    cv_settings['timeoutSecondsPerProperty'] = '600'
    cv_settings['searchDepthSteps'] = 500
    cv_settings['loopUnroll'] = 150
    cv_settings['maximumNumberOfThreads'] = config['SV_GEN_CV_NUMBER_OF_THREADS']
    cv_settings['coreEngines'] = []
    [cv_settings['coreEngines'].append({ 'name' : 'SMIBMC' })]
    [cv_settings['coreEngines'].append({ 'name' : 'VIS' })]
    [cv_settings['coreEngines'].append({ 'name' : 'CBMC' })]
    [cv_settings['coreEngines'].append({ 'name' : 'ISAT' })]
    # add cv engine to engine settings
    engine_settings['engineCv'] = cv_settings

    # prepare cv engine
    atg_settings = { 'name' : 'ATG' }
    atg_settings['timeoutSecondsPerSubsystem'] = 900
    atg_settings['executionMode'] = 'BOTTOM_UP'
    atg_settings['searchDepthSteps'] = 500
    # add cv engine to engine settings
    engine_settings['engineAtg'] = atg_settings

    vector_generation_config['engineSettings'] = engine_settings
    return vector_generation_config