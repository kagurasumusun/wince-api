import re,html,os
CACHE='build/pages'
def page_text(pid):
    root=pid.split('(')[0]
    f=os.path.join(CACHE,root+'.html')
    s=open(f,encoding='utf-8',errors='replace').read()
    s=re.sub(r'<script[\s\S]*?</script>','',s)
    s=re.sub(r'<style[\s\S]*?</style>','',s)
    s=re.sub(r'<br\s*/?>','\n',s)
    s=re.sub(r'</(p|div|li|tr|h1|h2|h3|pre|code)>','\n',s)
    s=re.sub(r'<[^>]+>',' ',s)
    s=html.unescape(s)
    s=re.sub(r'[ \t]+',' ',s)
    return s
