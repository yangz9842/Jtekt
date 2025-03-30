
import time
import os

from btc_embedded import EPRestApi, util, get_global_config
import yaml
import sys
print(sys.version)
WORKSPACE = sys.argv[1]
#WORKSPACE = WORKSPACE.replace('\\', '/')
MODELNAME = sys.argv[2]
SCRIPTNAME = MODELNAME.split('.')[0] + '_init.m'
Job_name = 'jtekt_JP'
FILE_SAVE_PLACE = WORKSPACE
print('executing file is ' + __file__)
print('working directroy is ' + WORKSPACE)

ep = EPRestApi( host = 'http://localhost',  port = 1337)

def getkeyfromressource(key, ressource):
  return ressource.get(key)

print("Step 1 Creating profile")
firststart = time.time()
response = ep.post('profiles?discardCurrentProfile=true')
end = time.time()

print("Step 1 completed")
print("Duration (in seconds): ")
print(end - firststart)
print('\n')

############################################
print("Step 2 model {} TL model import".format(MODELNAME))
start = time.time()

print(WORKSPACE + MODELNAME)
TL_import_payload = {
  "tlModelFile": WORKSPACE + MODELNAME,
  "tlInitScript": WORKSPACE + SCRIPTNAME,
  }



response = ep.post('architectures/targetlink', TL_import_payload)

end = time.time()
print("Step 2 completed")
print("Duration (in seconds): ")
print(end - start)        
print('\n')



############################################
print("Step 3 Generate stimuli vector from code coverage for B2B test and after that convert them to testcases")

start = time.time()
scopes = ep.get('scopes?top-level=true')

toplevel_scope_uid = scopes[0]['uid']

engine_setting = { 'scopeUid' : toplevel_scope_uid,
                    
                      'pllString': 'MCDC',
                      'engineSettings' : {
                          'timeoutSeconds' : 480 
                          }
                  }

ep.post('coverage-generation', engine_setting)
print('Stimuli Vectors are generated')

response = ep.post(f"scopes/{toplevel_scope_uid}/b2b", { 'refMode': 'TL MIL', 'compMode': 'SIL' })
print('Back to back test is done')

report = ep.post(f"scopes/{toplevel_scope_uid}/project-report")
ep.post(f"reports/{report['uid']}", { 'exportPath': FILE_SAVE_PLACE +  'B2B_reports/', 'newName': f'B2B_report_for_{MODELNAME}'})


end = time.time()
print("Step 3 completed")
print("Duration (in seconds): ")
print(end - start)
print('\n')

############################################

print("Step 4 profile export")
print(FILE_SAVE_PLACE +  'B2B_profiles/' + MODELNAME.split('.')[0] + '.epp')
ep.put('profiles',{'path' : FILE_SAVE_PLACE +  'B2B_profiles/' + MODELNAME.split('.')[0] + '.epp'})
ep.delete('profiles')

end = time.time()
print("Step 4 completed")
print("Duration (in seconds): ")
print(end - start)
print('\n')

############################################

