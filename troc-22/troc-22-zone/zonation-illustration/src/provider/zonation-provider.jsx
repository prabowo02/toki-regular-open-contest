import React, { useContext, useState } from 'react'
import getStudent from './predetermined-constants'

const ZonationContext = React.createContext()

export function useZonation() {
  return useContext(ZonationContext)
}

export function ZonationProvider({children}) {
  const [activeStudent, setActiveStudent] = useState(getStudent(0))

  function changeActiveStudent(studentId) {
    setActiveStudent(getStudent(studentId))
  }

  const value = {
    activeStudent, 
    changeActiveStudent,
  }

  return (
    <ZonationContext.Provider value={value}>
      {children}
    </ZonationContext.Provider>
  )
}

export default ZonationProvider
